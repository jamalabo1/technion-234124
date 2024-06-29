import utils
import subprocess


def test_target(target, command, exec, verify):
    print("running")
    utils.change_permission(target)
    subprocess.run(exec, shell=True)
    subprocess.run(verify, shell=True)
