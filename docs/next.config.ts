import type { NextConfig } from "next";

const nextConfig: NextConfig = {
  /* config options here */
  webpack: (config) => {
    config.experiments = {
      asyncWebAssembly: true,
    }
  }
};

export default nextConfig;
