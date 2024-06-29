from pathlib import Path

from engine import utils
from engine import common


def pytest_addoption(parser):
    parser.addoption(
        "--valgrind",
        action="store_true",
        default=False,
        help="run tests with valgrind"
    )


def pytest_generate_tests(metafunc):
    test_target_data = []
    settings = utils.load_settings()
    valgrind = metafunc.config.getoption("valgrind")

    for target in settings:
        utils.change_permission(target)

        options = settings[target]
        if "generated" in options:
            for op in options["generated"]:
                for test_case in Path(op["path"]).glob("*"):
                    path_vars = op["path_vars"]
                    variables = {key: test_case.joinpath(path_vars[key]) for key in path_vars}

                    commands = common.get_generated_test_commands(target, op, variables, valgrind)

                    test_target_data.append(
                        (
                            target,
                            op["command"],
                            commands["exec_command"],
                            commands["verify_command"]
                        )
                    )

    metafunc.parametrize("target,command,exec,verify", test_target_data)