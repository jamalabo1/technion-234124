import click
import engine.utils
from engine.runner import run_tests, run_valgrind


@click.command()
@click.option('--valgrind', is_flag=True, help='run valgrind checks on commands')
def cli(valgrind):
    settings = engine.utils.load_settings()
    for target in settings:
        if valgrind:
            run_valgrind(target, settings[target])
        else:
            run_tests(target, settings[target])
