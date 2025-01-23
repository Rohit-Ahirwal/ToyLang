import type { Metadata } from "next";
import "./globals.css";
import { Poppins } from "next/font/google";
import Footer from "@/components/Footer";

export const metadata: Metadata = {
  title: "ToyLang",
  description: "A Toy programming language written in C++",
  icons: "ToyLang.ico"
};

const poppins = Poppins({
  variable: "--font-poppins",
  subsets: ["latin"],
  weight: "100"
});

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en" className="scroll-smooth">
      <body
        className={`${poppins.variable} antialiased`}
      >
        {children}
        <Footer />
      </body>
    </html>
  );
}
