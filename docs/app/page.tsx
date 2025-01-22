'use client'
import ToyEditor from "@/components/ToyEditor";
import { Github } from "lucide-react";
import Link from "next/link";
import { useState } from "react";
import CodeBlock from "@/components/CodeBlock";

const initialCode = `
log("Hello World");

a = 3;
b = 0;

while (b < 10) {
  if (a > b) {
    log("a is greater than a");
  } elif (a < b) {
    log("b is greater than a");
  } else {
    log("b is equal to a");
  }

  b = b + 1;
}
`;

const variableCode = `a = 10;`;
const typesCode = `a = 10;
b = "Hello World!";
c = true;
`;
const builtinsCode = `log("Hello World!");`;
const conditionalsCode = `if (a > b) {
  log("a is greater than a");
} elif (a < b) {
  log("b is greater than a");
} else {
  log("b is equal to a");
}
`;
const forLoopCode = `for (i = 0; i < 10; i++) {
  log(i);
}
`;

const whileLoopCode = `while (i < 10) {
  log(i);
  i = i + 1;
}
`;

export default function Home() {
  const [code, setCode] = useState(initialCode);
  const [output, setOutput] = useState<string | null>(null);

  const executeCode = async () => {
    const response = await fetch('/api/execute', {
      method: 'POST',
      body: JSON.stringify({ code: code }),
      headers: {
        'Content-Type': 'application/json',
      },
    });

    const data = await response.json();

    if (data.error) {
      setOutput(data.error);
    } else {
      setOutput(data.output);
    }
  }


  const clearCode = () => {
    setCode('');
    setOutput(null);
  }

  return (
    <div className="p-4">
      <div className="w-full flex flex-col items-center min-h-screen text-center">
        <h1 className="text-6xl mt-40 mb-10 text-heading sm:text-9xl sm:mt-60 sm:mb-16">ToyLang</h1>
        <span>A Toy programming language written in C++</span>
        <div className="my-12">
          <Link href={`${process.env.NEXT_PUBLIC_REPO_URL}`} target="_blank">
            <button className="btn-github">
              <Github />
              <span>Rohit-Ahirwal/ToyLang</span>
            </button>
          </Link>
        </div>
        <div className="flex justify-center items-center gap-4">
          <Link href={"#playground"}>
            <button className="btn-primary">
              Playground
            </button>
          </Link>
          <Link href={`${process.env.NEXT_PUBLIC_REPO_URL}`} target="_blank">
            <button className="btn-secondary">
              Download
            </button>
          </Link>
        </div>
      </div>
      <div id="playground" className="my-4 sm:flex justify-between items-center">
        <div>
          <h4 className="text-heading text-4xl mb-5">Playground</h4>
        </div>
        <div className="flex justify-start items-center gap-4">
          <Link href={"#output"}>
            <button onClick={executeCode} className="btn-primary py-1 w-20">
              Run
            </button>
          </Link>
          <button onClick={clearCode} className="btn-secondary py-1 w-20">
            Clear
          </button>
        </div>
      </div>
      <ToyEditor code={code} onChange={(value) => setCode(value)} />
      <div id="output" className={`${output ? 'h-auto' : 'h-0'} my-4 overflow-hidden transition-all duration-300`}>
        <div className="bg-gray-800 text-white p-4 rounded-md">
          {output && (
            <pre className="whitespace-pre-wrap">{output}</pre>
          )}
        </div>
      </div>
      <div>
        <div className="py-20 px-10">
          <h4 className="text-heading text-4xl mb-5">Documentation</h4>
          <span>ToyLang is a dynamically typed programming language, designed for practice and educational use, and implemented in C++.</span>

          <div className="sm:grid grid-cols-2 gap-4 mt-10">
            <div>
              <h5 className="text-heading text-2xl mt-10 mb-5">Variables</h5>
              <span>Easily assign values to variables with statements like. <CodeBlock code={variableCode} language="toylang" /></span>
            </div>
            <div>
              <h5 className="text-heading text-2xl mt-10 mb-5">Types</h5>
              <span>ToyLang supports Number, String and Boolean etc. all these like other language. <CodeBlock code={typesCode} language="toylang" /></span>
            </div>
            <div>
              <h5 className="text-heading text-2xl mt-10 mb-5">Built-ins</h5>
              <span>You can use built-in log keyword to print anything to console. <CodeBlock code={builtinsCode} language="toylang" /></span>
            </div>
            <div>
              <h5 className="text-heading text-2xl mt-10 mb-5">Conditionals</h5>
              <span>
                ToyLang supports a simple if-elif-else construct to handle conditional logic.
                The if block executes when the condition is true, while the elif blocks can be used to check additional conditions in sequence.
                If none of the above conditions are true, the else block will execute, providing a default action when all conditions fail.
                This allows for clear and easy branching of program logic based on different conditions.
                <CodeBlock code={conditionalsCode} language="toylang" />
              </span>
            </div>
            <div>
              <h5 className="text-heading text-2xl mt-10 mb-5">For Loop</h5>
              <span>
                ToyLang provides a for loop for iterating over a specified range of values.
                It is ideal for situations where the number of iterations is known beforehand.
                You can define the start, condition, and step of the loop, making it easy to run repetitive tasks a set number of times.
                <CodeBlock code={forLoopCode} language="toylang" />
              </span>
            </div>
            <div>
              <h5 className="text-heading text-2xl mt-10 mb-5">While Loop</h5>
              <span>
                The while loop in ToyLang runs as long as a given condition is true.
                This loop is useful for situations where the number of iterations is not predetermined and the loop continues until a specific condition becomes false.
                It provides flexibility for running tasks based on dynamic conditions.
                <CodeBlock code={whileLoopCode} language="toylang" />
              </span>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}
