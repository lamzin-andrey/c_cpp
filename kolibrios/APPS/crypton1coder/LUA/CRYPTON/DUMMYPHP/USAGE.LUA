-- Подключаем модуль
local php = require("dummyphp")

-- Используем функции
php.echo("Hello", "World", 123)

local content = php.file_get_contents("test.txt")
print(content)

php.file_put_contents("output.txt", "Some data\n")
php.file_put_contents("output.txt", "Appended data\n", php.FILE_APPEND)

local count = {}
local result = php.str_replace("world", "Lua", "Hello world", count)
print(result)  -- Hello Lua
print("Replacements:", count[1])  -- 1

print(php.strlen("Hello"))  -- 5
print(php.substr("Hello World", 0, 5))  -- Hello
print(php.dechex(255))  -- ff
print(php.hexdec("ff"))  -- 255
print(php.date("Y-m-d H:i:s"))  -- 2024-01-15 12:30:45
print(php.time())  -- 1705321845
print(php.strtotime("2024-01-15"))  -- 1705276800


-- Подключаем модуль
local php = require("php_compat")

-- Выполняем команду
local last_line, output, return_code = php.exec("ls -la")

print("Последняя строка:", last_line)
print("Весь вывод:", output)
print("Код возврата:", return_code)

-- Собираем вывод в массив (как в PHP)
local output_lines = {}
local last_line, _, return_code = php.exec("ls", output_lines)

for i, line in ipairs(output_lines) do
    print(i .. ": " .. line)
end
