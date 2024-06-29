import subprocess


def test_target(target, command, exec, verify):
    subprocess.run(exec, shell=True)
    subprocess.run(verify, shell=True)
