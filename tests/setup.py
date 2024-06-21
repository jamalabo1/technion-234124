from setuptools import setup, find_packages

setup(
    name='engine',
    version='0.0.1',
    py_modules=['engine'],
    include_package_data=True,
    install_requires=[
        'Click',
    ],
    entry_points={
        'console_scripts': [
            'test_engine = engine.main:cli',
        ],
    },
)
