try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension


snake = Extension('snake',
                  define_macros = [('__PYTHON__', '1')],
                  sources = ['snake.c'])

setup(
    name = 'pysnake',
    author = 'Colin Stolley',
    author_email = 'cstolley@gmail.com',
    url = 'https://github.com/ccstolley/pysnake',
    version = '1.0',
    description = 'Fast Camel to Snake Case Converter',
    ext_modules = [snake],
    )
