-- ============================================================
-- php_compat.lua - Аналог PHP функций для Lua 5.2 (KolibriOS)
-- ============================================================

local php = {}

-- ============================================================
-- 1. echo - пишет в файл echo.txt в режиме append
-- Отличия: всегда пишет в файл echo.txt, а не в stdout
-- ============================================================
function php.echo(...)
    local file = io.open("echo.txt", "a")
    if not file then
        error("Cannot open echo.txt for writing")
    end

    local args = {...}
    for i, v in ipairs(args) do
        file:write(tostring(v))
        if i < #args then
            file:write("\t")  -- как в PHP разделяет аргументы пробелом
        end
    end
    file:write("\n")
    file:close()
end

-- ============================================================
-- 2. file_get_contents - читает файл целиком
-- Отличия: нет поддержки контекста и смещения
-- ============================================================
function php.file_get_contents(filename)
    local file = io.open(filename, "r")
    if not file then
        return nil, "Cannot open file: " .. filename
    end
    local content = file:read("*all")
    file:close()
    return content
end

-- ============================================================
-- 3. file_put_contents - запись в файл
-- Поддерживает FILE_APPEND (режим 'a')
-- Отличия: флаги передаются как строка 'a' для append
-- ============================================================
function php.file_put_contents(filename, data, flags)
    local mode = "w"
    if flags == "FILE_APPEND" or flags == "a" then
        mode = "a"
    end

    local file = io.open(filename, mode)
    if not file then
        return nil, "Cannot open file: " .. filename
    end

    file:write(data)
    file:close()
    return true
end

-- ============================================================
-- 4. str_replace - замена подстрок
-- Отличия:
--   - count передается по ссылке (таблица)
--   - не поддерживает массивы
-- ============================================================
function php.str_replace(search, replace, subject, count)
    if not count then
        count = {}
    end

    local result = subject
    local replacements = 0

    -- Если search и replace - строки
    if type(search) == "string" and type(replace) == "string" then
        local pos = 1
        while true do
            local start, finish = result:find(search, pos, true)
            if not start then
                break
            end
            result = result:sub(1, start - 1) .. replace .. result:sub(finish + 1)
            replacements = replacements + 1
            pos = start + #replace
        end
    end

    count[1] = replacements
    return result
end

-- ============================================================
-- 5. strlen - длина строки в байтах
-- Отличия: работает с байтами, не с символами UTF-8
-- ============================================================
function php.strlen(str)
    return #str
end

-- ============================================================
-- 6. substr - часть строки
-- Отличия: работает с байтами, не с символами UTF-8
-- ============================================================
function php.substr(str, start, length)
    if start < 0 then
        start = #str + start + 1
    else
        start = start + 1  -- PHP 0-based, Lua 1-based
    end

    if start < 1 then
        start = 1
    end

    if not length then
        return str:sub(start)
    end

    if length < 0 then
        length = #str + length - start + 2
    end

    if length <= 0 then
        return ""
    end

    return str:sub(start, start + length - 1)
end

-- ============================================================
-- 7. dechex - десятичное в шестнадцатеричное
-- Отличия: возвращает строку без префикса '0x'
-- ============================================================
function php.dechex(number)
    return string.format("%x", number)
end

-- ============================================================
-- 8. hexdec - шестнадцатеричное в десятичное
-- Отличия: принимает строку с hex числом
-- ============================================================
function php.hexdec(hex)
    return tonumber(hex, 16) or 0
end

-- ============================================================
-- 9. date - форматирование даты
-- Поддерживает: Y-m-d H:i:s
-- Отличия: только базовый формат
-- ============================================================
function php.date(format, timestamp)
    if not timestamp then
        timestamp = os.time()
    end

    local dt = os.date("*t", timestamp)

    -- Только базовые замены
    local result = format
    result = result:gsub("Y", string.format("%04d", dt.year))
    result = result:gsub("m", string.format("%02d", dt.month))
    result = result:gsub("d", string.format("%02d", dt.day))
    result = result:gsub("H", string.format("%02d", dt.hour))
    result = result:gsub("i", string.format("%02d", dt.min))
    result = result:gsub("s", string.format("%02d", dt.sec))

    return result
end

-- ============================================================
-- 10. time - текущий timestamp
-- Отличий нет
-- ============================================================
function php.time()
    return os.time()
end

-- ============================================================
-- 11. strtotime - преобразование строки в timestamp
-- Отличия:
--   - Ограниченная поддержка форматов
--   - Только форматы типа "2024-01-15" или "2024-01-15 12:30:45"
-- ============================================================
function php.strtotime(str)
    -- Формат: YYYY-MM-DD
    local year, month, day = str:match("^(%d+)%-(%d+)%-(%d+)")
    if year then
        return os.time({
            year = tonumber(year),
            month = tonumber(month),
            day = tonumber(day),
            hour = 0,
            min = 0,
            sec = 0
        })
    end

    -- Формат: YYYY-MM-DD HH:MM:SS
    year, month, day, hour, min, sec = str:match("^(%d+)%-(%d+)%-(%d+)%s+(%d+):(%d+):(%d+)")
    if year then
        return os.time({
            year = tonumber(year),
            month = tonumber(month),
            day = tonumber(day),
            hour = tonumber(hour),
            min = tonumber(min),
            sec = tonumber(sec)
        })
    end

    return nil, "Unsupported date format"
end


-- ============================================================
-- exec - аналог PHP функции exec
-- Отличия от PHP:
--   1. Возвращает таблицу с полями: output, code, signal
--   2. В KolibriOS использует os.execute() который возвращает код завершения
--   3. output - это строка с объединенным выводом (stdout + stderr)
--   4. Не поддерживает передачу переменных окружения
--   5. Вместо & для фонового режима используйте os.execute() напрямую

-- Пример
-- Собираем вывод в массив (как в PHP)
-- local output_lines = {}
-- local last_line, _, return_code = php.exec("ls", output_lines)

-- for i, line in ipairs(output_lines) do
--     print(i .. ": " .. line)
-- end


-- ============================================================
function php.exec(command, output_table, return_var)
    -- В Lua 5.2 os.execute возвращает:
    --   true, "exit", code - если команда завершилась с кодом code
    --   nil, "exit", code - если команда завершилась с ошибкой
    --   nil, "signal", signal - если команда была прервана сигналом

    local output = ""

    -- В KolibriOS стандартный способ выполнить команду и получить вывод
    -- Используем io.popen если доступен, иначе только os.execute
    local pipe = io.popen(command .. " 2>&1", "r")

    if pipe then
        -- Читаем весь вывод
        output = pipe:read("*all")
        pipe:close()

        -- Получаем код возврата (для popen используем pipe:close() который возвращает код)
        -- В Lua 5.2 close возвращает статус, код и тип завершения
        local ok, exit_type, code = pipe:close()
        if exit_type == "exit" then
            return_var = code or 0
        else
            return_var = -1  -- сигнал или ошибка
        end
    else
        -- fallback: просто выполняем команду без захвата вывода
        local result, exit_type, code = os.execute(command)
        if exit_type == "exit" then
            return_var = code or 0
        else
            return_var = -1
        end
        output = ""  -- не можем получить вывод
    end

    -- Если передан output_table, заполняем его как в PHP
    if output_table then
        -- Разбиваем вывод на строки
        for line in string.gmatch(output, "[^\n]*\n?") do
            if line ~= "" then
                table.insert(output_table, line:gsub("\n$", ""))
            end
        end
    end

    -- Возвращаем последнюю строку вывода (как в PHP)
    local lines = {}
    for line in string.gmatch(output, "[^\n]+") do
        table.insert(lines, line)
    end

    return lines[#lines] or "", output, return_var
end


-- ============================================================
-- explode - аналог PHP функции explode
-- Отличия от PHP:
--   1. limit работает как в PHP (положительный, отрицательный, 0)
--   2. Возвращает таблицу с индексами начиная с 1 (как в Lua)
--   3. При отрицательном limit возвращает все кроме последних N частей
-- ============================================================
function php.explode(delimiter, string, limit)
    if not string or string == "" then
        return {}
    end

    if not limit then
        limit = 0  -- 0 означает "все части" как в PHP
    end

    local result = {}

    -- Если разделитель пустой - разбиваем по символам
    if delimiter == "" then
        for i = 1, #string do
            table.insert(result, string:sub(i, i))
        end

        -- Применяем limit
        if limit > 0 and #result > limit then
            local trimmed = {}
            for i = 1, limit do
                table.insert(trimmed, result[i])
            end
            return trimmed
        elseif limit < 0 then
            local n = #result + limit
            if n < 0 then n = 0 end
            local trimmed = {}
            for i = 1, n do
                table.insert(trimmed, result[i])
            end
            return trimmed
        end

        return result
    end

    -- Стандартное разбиение
    local pos = 1
    local parts_count = 0

    -- Для положительного limit нужно собрать ровно limit частей
    if limit > 0 then
        while parts_count < limit - 1 do
            local start, finish = string:find(delimiter, pos, true)
            if not start then
                break
            end
            table.insert(result, string:sub(pos, start - 1))
            pos = finish + 1
            parts_count = parts_count + 1
        end
        -- Добавляем остаток строки
        table.insert(result, string:sub(pos))
        return result
    end

    -- limit = 0 или nil - все части
    while true do
        local start, finish = string:find(delimiter, pos, true)
        if not start then
            table.insert(result, string:sub(pos))
            break
        end
        table.insert(result, string:sub(pos, start - 1))
        pos = finish + 1
    end

    -- Отрицательный limit - обрезаем последние N частей
    if limit < 0 then
        local n = #result + limit
        if n < 0 then n = 0 end
        local trimmed = {}
        for i = 1, n do
            table.insert(trimmed, result[i])
        end
        return trimmed
    end

    return result
end

-- ============================================================
-- implode - аналог PHP функции implode (и join)
-- Отличия: работает так же как в PHP
-- ============================================================
function php.implode(glue, pieces)
    -- Если glue это таблица, а pieces строка (как в PHP вариация join)
    if type(glue) == "table" and (not pieces or type(pieces) == "string") then
        -- Меняем местами: pieces = glue, glue = pieces или ""
        local temp = pieces or ""
        pieces = glue
        glue = temp
    end

    -- Если pieces не таблица, возвращаем как строку
    if type(pieces) ~= "table" then
        return tostring(pieces or "")
    end

    -- Объединяем таблицу
    local result = {}
    for i, v in ipairs(pieces) do
        table.insert(result, tostring(v))
    end

    return table.concat(result, tostring(glue or ""))
end


function php.__FILE__(info)
    -- Получаем информацию о функции на 1-м уровне стека (текущая)
    -- local info = debug.getinfo(1, "S")
    -- Поле source содержит имя файла с префиксом '@'
    return info.source
end

function php.__DIR__(path)
    -- local path = php.__FILE__()
    -- Убираем префикс '@' и отделяем имя файла от пути к каталогу
    local dir = path:match("^@?(.+/)[^/]+$")
    if dir then
        return dir
    else
        -- Если файл в корне, возвращаем текущую директорию
        return "./"
    end
end

-- Использование
-- print("Путь к файлу: " .. getScriptPath())   -- Вывод: @/home/user/script.lua
-- print("Директория: " .. getScriptDir())      -- Вывод: /home/user/




-- ============================================================
-- Вспомогательные функции для совместимости
-- ============================================================

-- FILE_APPEND константа (симуляция)
php.FILE_APPEND = "FILE_APPEND"

-- ============================================================
-- Возвращаем модуль
-- ============================================================
return php
