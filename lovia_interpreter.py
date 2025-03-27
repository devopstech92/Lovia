import re

# Lovia Interpreter
class LoviaInterpreter:
    def __init__(self):
        self.variables = {}
    
    def evaluate_expression(self, expression):
        for var in self.variables:
            expression = expression.replace(var, str(self.variables[var]))
        try:
            return eval(expression)
        except Exception:
            return expression
    
    def execute(self, code_lines):
        i = 0
        while i < len(code_lines):
            line = code_lines[i].strip()
            
            if line.startswith("say "):
                print(self.evaluate_expression(line[4:].strip()))
            
            elif line.startswith("set "):
                match = re.match(r"set (\w+) to (.+)", line)
                if match:
                    var_name, value = match.groups()
                    self.variables[var_name] = self.evaluate_expression(value)
            
            elif line.startswith("if "):
                match = re.match(r"if (.+):", line)
                if match:
                    condition = self.evaluate_expression(match.group(1))
                    if not condition:
                        while i < len(code_lines) and not code_lines[i].startswith("else:"):
                            i += 1  # Skip lines if condition is False
            
            elif line.startswith("repeat "):
                match = re.match(r"repeat (\d+) times:", line)
                if match:
                    count = int(match.group(1))
                    start = i + 1
                    loop_body = []
                    while start < len(code_lines) and not code_lines[start].strip().endswith(":end"):
                        loop_body.append(code_lines[start])
                        start += 1
                    for _ in range(count):
                        self.execute(loop_body)
                    i = start  # Skip loop body after execution
            
            i += 1

# Run the Lovia Interpreter
if __name__ == "__main__":
    with open("example.lovia", "r") as file:
        code = file.readlines()
    interpreter = LoviaInterpreter()
    interpreter.execute(code)
