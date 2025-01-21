import React, { useEffect } from 'react';
import Editor, { loader } from '@monaco-editor/react';

interface ToyEditorProps {
  code: string;
  onChange: (value: string) => void;
}

// ToyLang rules
const toylangConfig = {
  defaultToken: '',
  tokenPostfix: '.toy',

  keywords: (process.env.NEXT_PUBLIC_TOYLANG_KEYWORDS || '').split(','),

  operators: (process.env.NEXT_PUBLIC_TOYLANG_OPERATORS || '').split(','),

  tokenizer: {
    root: [
      // Keywords
      [/\b(?:if|elif|else|while|for|log|true|false)\b/, 'keyword'],

      // Identifiers
      [/[a-zA-Z_$][\w$]*/, 'identifier'],

      // Numbers
      [/\d+/, 'number'],

      // Operators
      [/[=><!|+\-*\/\^%]+/, 'operator'],

      // Strings
      [/"([^"\\]|\\.)*$/, 'string.invalid'], // Unterminated string
      [/"([^"\\]|\\.)*"/, 'string'],
    ],
  },
};

// Language configuration
const languageConfig = {
  comments: {
    lineComment: '//',
    blockComment: ['/*', '*/'],
  },
  brackets: [['{', '}'], ['[', ']'], ['(', ')']],
  autoClosingPairs: [
    { open: '{', close: '}' },
    { open: '[', close: ']' },
    { open: '(', close: ')' },
    { open: '"', close: '"' },
  ],
};

const ToyEditor: React.FC<ToyEditorProps> = ({ code, onChange }) => {

  useEffect(() => {
    loader.init().then((monaco) => {
      // Register the ToyLang language
      monaco.languages.register({ id: 'toylang' });

      // Set language configuration
      monaco.languages.setMonarchTokensProvider('toylang', toylangConfig);
      monaco.languages.setLanguageConfiguration('toylang', languageConfig);

      monaco.languages.registerCompletionItemProvider('toylang', {
        provideCompletionItems: () => {
          const suggestions = [
            {
              label: 'if',
              kind: monaco.languages.CompletionItemKind.Keyword,
              insertText: 'if (${1:condition}) {\n\t$0\n}',
              insertTextRules:
                monaco.languages.CompletionItemInsertTextRule.InsertAsSnippet,
              documentation: 'If statement',
            },
            {
              label: 'for',
              kind: monaco.languages.CompletionItemKind.Keyword,
              insertText: 'for (${1:i = 0; i < n; i++}) {\n\t$0\n}',
              insertTextRules:
                monaco.languages.CompletionItemInsertTextRule.InsertAsSnippet,
              documentation: 'For loop',
            },
            {
              label: 'while',
              kind: monaco.languages.CompletionItemKind.Keyword,
              insertText: 'while (${1:condition}) {\n\t$0\n}',
              insertTextRules:
                monaco.languages.CompletionItemInsertTextRule.InsertAsSnippet,
              documentation: 'While loop',
            },
            {
              label: 'log',
              kind: monaco.languages.CompletionItemKind.Function,
              insertText: 'log(${1:message});',
              insertTextRules:
                monaco.languages.CompletionItemInsertTextRule.InsertAsSnippet,
              documentation: 'Log a message to the console',
            },
            {
              label: 'true',
              kind: monaco.languages.CompletionItemKind.Keyword,
              insertText: 'true',
              documentation: 'Boolean true value',
            },
            {
              label: 'false',
              kind: monaco.languages.CompletionItemKind.Keyword,
              insertText: 'false',
              documentation: 'Boolean false value',
            },
          ];
          return { suggestions };
        },
      });
    });
  }, []);

  return (
    <Editor
      height="500px"
      theme='vs-dark'
      defaultLanguage="toylang"
      value={code}
      onChange={(value) => onChange(value || '')}
      options={{
        minimap: { enabled: false },
        wrapline: 'on',
        wordWrap: 'on',
      }}
    />
  );
};

export default ToyEditor;
