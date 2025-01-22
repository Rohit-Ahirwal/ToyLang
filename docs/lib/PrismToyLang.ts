import Prism from 'prismjs'

Prism.languages.toylang = {
    'keyword': /\b(?:if|elif|else|while|for|log|true|false)\b/,
    'boolean': /\b(true|false)\b/,
    'number': /\b\d+(\.\d+)?\b/,
    'operator': /[=><!|+\-*\/\^%]+/,
    'punctuation': /[{}();,]/,
    'string': {
        pattern: /"(?:\\.|[^"\\])*"/,
        greedy: true
    },
    'comment': {
        pattern: /#.*/,
        greedy: true
    },
    'identifier': /[a-zA-Z_]\w*/,
};



export default Prism;