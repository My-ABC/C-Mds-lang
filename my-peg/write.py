from contextlib import contextmanager

class Writer:
    def __init__(self):
        self._line = 0
        self._indent = 0
        self._out = ""

    def clear(self):
        self._line = 0
        self._indent = 0
        self._out = ""

    def write(self, s):
        self._out += self._indent * (" " * 4) + s
        return self
    
    @contextmanager
    def indent(self):
        try:
            self._indent += 1
            yield 
        finally:
            self._indent -= 1
            ...

    def get(self):
        return self._out