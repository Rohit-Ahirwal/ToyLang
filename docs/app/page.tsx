'use client'
import { Editor, type Monaco } from "@monaco-editor/react";
import { Github } from "lucide-react";
import Link from "next/link";
import { useState } from "react";

export default function Home() {
  const [code, setCode] = useState("");

  return (
    <div className="p-8">
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
          <Link href={`${process.env.NEXT_PUBLIC_REPO_URL}`} target="_blank">
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
      <Editor
        height="400px"
        defaultLanguage="javascript" // Customize for your language syntax highlighting
        value={code}
        theme="vs-dark"
        onChange={(newValue) => setCode(newValue || "")}
      />
    </div>
  );
}
