"""
This script reads integration
bounds and a function from
standard input, validates the
input format, and outputs the
corresponding LaTeX
representation of a definite
integral.

Input Format:
    - The first line should
      start with "Bounds   : "
      followed by two
      comma-separated values
      (e.g., "a, b").
    - The second line should
      start with "Function : "
      followed by a
      mathematical expression
      in terms of x.

Functionality:
    - Parses and validates the
      bounds and function using
      sympy.
    - Outputs the LaTeX code
      for the definite integral
      of the given function
      over the specified bounds.

Error Handling:
    - Handles invalid input
      formats, unexpected end
      of input, value errors,
      attribute errors, and
      user interruptions.

"""

import sys
import sympy


def read(start: str) -> str:
    """Read input starting with a specific prefix."""
    line = input()
    if not line.startswith(start):
        print(f"Invalid input format. Expected '{start}...'", file=sys.stderr)
        sys.exit(1)
    ret = line[len(start) :].strip()
    if not ret:
        print(f"Invalid input format. Expected '{start}...'", file=sys.stderr)
        sys.exit(1)
    return ret


if __name__ == "__main__":
    try:
        bounds = read("Bounds   : ")
        bounds = bounds.split(", ")
        if len(bounds) != 2:
            print("Invalid bounds format. Expected 'a, b'", file=sys.stderr)
            sys.exit(1)
        bounds = tuple(map(sympy.sympify, bounds))
        bounds = tuple(map(sympy.latex, bounds))

        function = read("Function : ")
        function = sympy.latex(sympy.sympify(function).simplify())

        print(f"\\int_{{{bounds[0]}}}^{{{bounds[1]}}} {function} \\mathrm{{d}}x")
    except EOFError:
        print("Input ended unexpectedly.", file=sys.stderr)
        sys.exit(1)
    except ValueError as ve:
        print(f"Value error: {ve}", file=sys.stderr)
        sys.exit(1)
    except AttributeError as ae:
        print(f"Attribute error: {ae}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:  # pylint: disable=broad-exception-caught
        print(f"Error processing input: {e}", file=sys.stderr)
        sys.exit(1)
    except KeyboardInterrupt:
        print("Process interrupted by user.", file=sys.stderr)
        sys.exit(1)
