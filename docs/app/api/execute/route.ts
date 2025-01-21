import { exec } from 'child_process';
import { promisify } from 'util';
import fs from 'fs/promises';
import path from 'path';
import { NextResponse } from 'next/server';

const execAsync = promisify(exec); // Promisify exec for async/await

export async function POST(request: Request): Promise<Response> {
    try {
        const { code }: { code?: string } = await request.json();

        if (!code) {
            return NextResponse.json({ error: 'Code is required', status: 400 });
        }

        const filePath = path.join(process.cwd(), 'temp.toy'); // Temporary file path
        const execPath = path.join(process.cwd(), 'public', 'ToyLang.exe'); // Absolute path to the executable

        // Write the code to a temporary file
        await fs.writeFile(filePath, code, 'utf8');

        // Execute the ToyLang executable
        const { stdout, stderr } = await execAsync(`"${execPath}" "${filePath}"`);

        // Clean up the temporary file
        await fs.unlink(filePath);

        if (stderr) {
            return NextResponse.json({ error: stderr });
        }

        return NextResponse.json({ output: stdout });
    } catch (err) {
        return NextResponse.json({
            error: 'Failed to execute code',
            details: (err as Error).message,
            status: 500,
        });
    }
}
