#define PY_SSIZE_T_CLEAN
#include <Python.h>

struct module_state {
    PyObject *error;
};
static PyObject * to_snake_unicode(Py_UNICODE *camel_word, Py_ssize_t length);


/*
 * Encode camel case as snake case fast.
 */
static PyObject *
to_snake(PyObject *self, PyObject *args)
{
    Py_UNICODE *camel_u = NULL;
    char *camel_s = NULL;
    Py_ssize_t length = 0;

    if (!PyArg_ParseTuple(args, "u#", &camel_u, &length)) {
       	return NULL;
    }
    else {
        return to_snake_unicode(camel_u, length);
    }
}

static
PyObject *
to_snake_unicode(Py_UNICODE *camel_word, Py_ssize_t length) {
    Py_UNICODE *snake_word, *c, *s;
    PyObject *snake_py = NULL;
    Py_ssize_t snake_length = 0, i = 0;

	if (length == 0) {
        return PyUnicode_FromStringAndSize("", 0);
    }

    snake_length = (length * 2) + 1; /* allocate twice the size to avoid space probs */
    snake_word = calloc(snake_length, sizeof(Py_UNICODE));
    s = snake_word;
    c = camel_word;

    for (i=0; i<length;) {
        if (i < length - 2 && Py_UNICODE_ISUPPER(c[i]) && Py_UNICODE_ISUPPER(c[i+1]) && Py_UNICODE_ISLOWER(c[i+2])) {
            *s++ = Py_UNICODE_TOLOWER(c[i]);
            i++;
            *s++ = '_';
            *s++ = Py_UNICODE_TOLOWER(c[i]);
            i++;
            *s++ = Py_UNICODE_TOLOWER(c[i]);
            i++;
        } else if ((Py_UNICODE_ISLOWER(c[i]) || Py_UNICODE_ISDIGIT(c[i])) && Py_UNICODE_ISUPPER((c[i + 1]))) {
            *s++ = c[i];
            i++;
            *s++ = L'_';
            while (i+1 < length && Py_UNICODE_ISLOWER(c[i]) && !Py_UNICODE_ISUPPER(c[i + 1])) {
                *s++ = c[i];
                i++;
            }
        } else if (c[i] == L'-') {
            *s++ = L'_';
            i++;
        } else {
            *s++ = Py_UNICODE_TOLOWER(c[i]);
            i++;
        }
    }
    *s = L'\0';
    snake_py = Py_BuildValue("u#", snake_word, s - snake_word);
    free(snake_word);
    return snake_py;
};

static PyMethodDef snake_methods[] = {
    {"to_snake", to_snake, METH_VARARGS, "Convert a string to snake_case very quickly."},
            {NULL, NULL, 0, NULL}
};


static struct PyModuleDef snakedef = {
    PyModuleDef_HEAD_INIT,
    "to_snake",
    "Convert a string to snake_case very quickly.",
    sizeof(struct module_state),
    snake_methods,
    NULL,
    NULL,
    NULL,
    NULL,
};

PyMODINIT_FUNC
PyInit_snake(void) {
    return PyModule_Create(&snakedef);
}

