import argparse
import json
import sys


class Enigma:
    # initializes a new instance of the class with the values provided for 'hash_map','wheels','reflector_map'
    def __init__(self, hash_map, wheels, reflector_map):
        self.hash_map = hash_map
        self.wheels = wheels
        self.reflector_map = reflector_map
        # creating a source copy of wheels so that each message return the wheels to their intial state
        self.original_wheels = wheels[:]
        self.encrypted_count = 0

    def encrypt_char(self, c):

        if c not in self.hash_map:
            return c, False

        i = self.hash_map[c]

        num = (self.wheels[0] * 2 - self.wheels[1] + self.wheels[2]) % 26
        if num == 0:
            i += 1
        else:
            i += num

        i = i % 26

        c1 = None
        for key, value in self.hash_map.items():
            if value == i:
                c1 = key
                break

        c2 = self.reflector_map[c1]
        i = self.hash_map[c2]

        num = (self.wheels[0] * 2 - self.wheels[1] + self.wheels[2]) % 26
        if num == 0:
            i -= 1
        else:
            i -= num

        i = i % 26

        c3 = None
        for key, value in self.hash_map.items():
            if value == i:
                c3 = key
                break

        return c3, True

    def incrementing_wheels(self):
        self.wheels[0] += 1
        if self.wheels[0] > 8:
            self.wheels[0] = 1

        if self.encrypted_count % 2 == 0:
            self.wheels[1] *= 2
            if self.wheels[1] > 8:
                self.wheels[1] = 1  # handles overflow
        else:
            self.wheels[1] -= 1

        if self.encrypted_count % 10 == 0:
            self.wheels[2] = 10

        elif self.encrypted_count % 3 == 0:
            self.wheels[2] = 5
        else:
            self.wheels[2] = 0

    def encrypt(self, message):
        encrypt_message = ""
        self.encrypted_count = 0

        for c in message:
            encrypted_char, affected = self.encrypt_char(c)
            encrypt_message += encrypted_char
            if affected:
                self.encrypted_count += 1
            self.incrementing_wheels()

        self.wheels = self.original_wheels[:]
        return encrypt_message


class JSONFileError(Exception):
    pass


def load_enigma_from_path(path):
    try:
        with open(path, 'r') as file:
            config = json.load(file)
            return Enigma(config['hash_map'], config['wheels'], config['reflector_map'])
    except Exception as err:
        raise JSONFileError(f"Error Loading Engima configuration: {str(err)}")


def main():
    parser = argparse.ArgumentParser(description="Encrypt messages using an Enigma machine configuration.")
    parser.add_argument('-c', '--config', required=True, help="Path to the Enigma configuration file(JSON).")
    parser.add_argument('-i', '--input', required=True, help="Path to the input file containing messages to encrypt.")
    parser.add_argument('-o', '--output',
                        help="Path to the output file to write encryptes messages. If not provided, messages will be printed to the console.")

    args = parser.parse_args()

    try:
        enigma_machine = load_enigma_from_path(args.config)
    except JSONFileError as e:
        print("The enigma script has encountered an error", file=sys.stderr)
        sys.exit(1)

    try:
        with open(args.input, 'r') as input_file:
            encrypted_messages = []
            for line in input_file:
                line = line.strip()
                encrypted_message = enigma_machine.encrypt(line)
                encrypted_messages.append(encrypted_message)

        if args.output:
            with open(args.output, 'w') as output_file:
                for message in encrypted_messages:
                    output_file.write(message + '\n')
        else:
            for message in encrypted_messages:
                print(message)

    except Exception as e:
        print("The enigma script has encountered an error", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
