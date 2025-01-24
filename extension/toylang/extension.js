const vscode = require('vscode');

/**
 * Activates the extension
 * @param {vscode.ExtensionContext} context
 */

function activate(context) {
  const runCommand = vscode.commands.registerCommand("ToyLang.runFile", () => {
    const editor = vscode.window.activeTextEditor
    if (!editor) {
      vscode.window.showErrorMessage("No file is open to run.")
      return
    }

    const filePath = editor.document.fileName
    const command = `ToyLang "${filePath}"`

    const terminal = vscode.window.createTerminal("ToyLang");
    terminal.sendText(command);
    terminal.show();

  })

  context.subscriptions.push(runCommand)
}

function deactivate() {}

module.exports = {
  activate,
  deactivate
}