import { ArrowLeft } from 'lucide-react';
import Image from 'next/image';
import Link from 'next/link';
import React from 'react';

const Download: React.FC = () => {
  return (
    <div>
      {/* Hero Section */}
      <section className="py-16 px-8 text-center">
        <h1 className="text-5xl text-heading font-[Amazone]">Download</h1>
        <p className="text-lg mb-8">Available for Linux and Windows now!</p>
      </section>

      {/* Main Download Section */}
      <section className="container mx-auto px-4 py-16 grid grid-cols-1 md:grid-cols-2 gap-8">
        {/* Linux Download Section */}
        <div className="bg-white/10 isolate ring-white/5 ring-1 backdrop-blur-md aspect-video rounded-xl shadow-xl p-8 text-center">
          <h2 className="text-3xl font-semibold mb-4">Linux</h2>
          <Image src="/os/linux.webp" width={100} height={100} alt="Linux Logo" className='mx-auto my-8' />
          <p className="text-lg mb-6">Ready to install on Linux. Choose your preferred package below.</p>
          <a href="/build/linux/ToyLang-linux-Installer.tar.gz" download className="bg-black hover:bg-black/80 text-white font-bold py-3 px-6 rounded-full transition duration-300">
            Download for Linux
          </a>
        </div>

        {/* Windows Download Section */}
        <div className="bg-white/10 isolate ring-white/5 ring-1 backdrop-blur-md aspect-video rounded-xl shadow-xl p-8 text-center">
          <h2 className="text-3xl font-semibold mb-4">Windows</h2>
          <Image src="/os/windows.webp" width={100} height={100} alt="Linux Logo" className='mx-auto my-8' />
          <p className="text-lg mb-6">Compatible with Windows. Get started now.</p>
          <a href="/build/windows/ToyLangInstaller.exe" download className="bg-indigo-600 hover:bg-indigo-600/80 text-white font-bold py-3 px-6 rounded-full transition duration-300">
            Download for Windows
          </a>
        </div>

        {/* Mac Download Section */}
        <div className="bg-white/10 isolate ring-white/5 ring-1 backdrop-blur-md aspect-video rounded-xl shadow-xl p-8 text-center sm:col-span-2 sm:justify-self-center">
          <h2 className="text-3xl font-semibold mb-4">MacOs</h2>
          <Image src="/os/mac.webp" width={100} height={100} alt="Linux Logo" className='mx-auto my-8' />
          <p className="text-lg mb-6">We're working on the Mac version. Stay tuned!</p>
        </div>
      </section>

      <Link href="/" className='btn-primary flex items-center w-fit mx-auto gap-2 px-4 py-2 rounded-full text-white hover:bg-black/10 transition duration-300'>
        <ArrowLeft />
        <span>Back to Homepage</span>
      </Link>
    </div>
  );
};

export default Download;
