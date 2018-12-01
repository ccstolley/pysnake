# pysnake
Convert camel to snake case really fast.

Requires Python 3.

Using regexes to convert camel case to snake is incredibly slow.
If you're doing this a lot, it can quickly become a bottleneck in
your code. This module is written in C and uses only simple string
operations to convert, and is thus very fast.

```
>>> import snake
>>> snake.to_snake('thisIsTheBestThingEver')
'this_is_the_best_thing_ever'
```

Rough Benchmark
--
```
>>> import timeit
>>> import snake
>>> import re
>>> first_cap_re = re.compile('(.)([A-Z][a-z]+)')
>>> all_cap_re = re.compile('([a-z0-9])([A-Z])')
>>> def convert(name):
...     s1 = first_cap_re.sub(r'\1_\2', name)
...     return all_cap_re.sub(r'\1_\2', s1).lower()
...
>>> timeit.timeit('convert("thisIsntTheOnlyTestYouCanRunButItsAFairlyDecentOne")', globals=globals(), number=100000)
8.081034302012995
>>> timeit.timeit('snake.to_snake("thisIsntTheOnlyTestYouCanRunButItsAFairlyDecentOne")', globals=globals(), number=100000)
0.29105806298321113
```
