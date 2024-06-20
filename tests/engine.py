import json
from typing import List
import subprocess


class TestBlock:
    commands: List
    key: str

    def __init__(self, commands, key):
        self.commands = commands
        self.key = key


def run_blocks(blocks: List[TestBlock]):
    for block in blocks:
        print(f"----- {block.key} -----")

        for command in block.commands:
            print(f"running command: {command}")
            try:
                subprocess.check_output(command, shell=True)
            except subprocess.CalledProcessError as e:
                print(f"***failed command***: {command}")
                print(e.output)

        print(f"----- {block.key} -----")


def run_tests(target: str, options):
    blocks: List[TestBlock] = []

    if "explict" in options:
        for op in options["explict"]:
            args = ""
            include = False if ("include" in op and (op["include"] is False)) else True
            if include:
                args = f" {op['source']} {op['target']}"

            exc_command = f"./{target} {op['command']}{args}"

            verify_command = f"diff --strip-trailing-cr -B -Z {op['source']} {op['target']} "

            key = op["key"] if "key" in op else op["command"]

            blocks.append(
                TestBlock(
                    [
                        exc_command,
                        verify_command
                    ],
                    key
                )
            )

    run_blocks(blocks)


def main():
    settings_file = open("settings.json", "r")
    settings = json.load(settings_file)

    for target in settings:
        run_tests(target, settings[target])


if __name__ == "__main__":
    main()
