import React, { useEffect } from 'react';
import Prism from 'prismjs';
import '@/lib/PrismToyLang';
import 'prismjs/themes/prism-okaidia.css';
import 'prismjs/plugins/toolbar/prism-toolbar.css';
import 'prismjs/plugins/toolbar/prism-toolbar';
import 'prismjs/plugins/copy-to-clipboard/prism-copy-to-clipboard';

interface CodeBlockProps {
    code: string,
    language: string
}

const CodeBlock: React.FC<CodeBlockProps> = ({ code, language }) => {

    useEffect(() => {
        if (typeof window !== 'undefined') {
            Prism.highlightAll();
            Prism.plugins.toolbar.registerButton('copy-to-clipboard', {
                text: 'Copy',
                onClick: function (env: { element: HTMLElement; }) {
                    Prism.plugins.copyToClipboard.copy(env.element);
                }
            });
        }
    }, [])

    return (
        <pre className={`rounded-md p-4 language-${language}`}>
            <code className={`language-${language}`} data-prismjs-copy={"copy"}>
                {code}
            </code>
        </pre>
    )
}

export default CodeBlock