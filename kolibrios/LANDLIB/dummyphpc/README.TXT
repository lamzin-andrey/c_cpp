file_put_contents осторожно, пока использовал
file_put_contents
сразу после него не работал
file_get_contents

Заменил на
file_put_contentsа
file_get_contents
всё заработало.


Также не работало чтение (не всегда работало!), пока не выполнил предварительно file_exists
