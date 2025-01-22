import Link from 'next/link'
import React from 'react'

const Footer = () => {
  return (
    <div className='flex flex-col items-center justify-center py-8'>
        <span>© 2025 <Link href={`${process.env.NEXT_PUBLIC_PORTFOLIO_URL}`} target='_blank' className='hover:text-heading'>Rohit Ahirwal</Link></span>
    </div>
  )
}

export default Footer