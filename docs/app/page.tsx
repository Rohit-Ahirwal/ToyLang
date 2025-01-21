'use client'
import ToyEditor from "@/components/ToyEditor";
import { Github } from "lucide-react";
import Link from "next/link";
import { useState } from "react";

const sampleCode = `
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

export default function Home() {
  const [code, setCode] = useState(sampleCode);
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
    </div>
  );
}
