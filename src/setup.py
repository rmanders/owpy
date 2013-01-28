from distutils.core import setup, Extension
import os

cwd=os.getcwd()
owlink=cwd+'/onewiresdk/lib/other/libUSB'
owcommon=cwd+'/onewiresdk/common'

owpy = Extension('owpy',
		include_dirs=[owcommon, owlink, cwd],
		libraries=['usb'],
		sources = ['owpy.c',
			owlink+'/libusbds2490.c',
			owlink+'/libusblnk.c',
			owlink+'/libusbses.c',
			owlink+'/libusbnet.c',
			owlink+'/libusbtran.c',
			owcommon+'/owerr.c',
			owcommon+'/ioutil.c',
			owcommon+'/maxq1004.c',
			owcommon+'/crcutil.c',
			owcommon+'/temp10.c',
			owcommon+'/temp28.c',
			owcommon+'/tempall.c',
			owcommon+'/cnt1d.c'])

setup (name = 'owpy',
		version = '1.0',
		description = 'Basic 1-wire library functions',
		ext_modules = [owpy])
