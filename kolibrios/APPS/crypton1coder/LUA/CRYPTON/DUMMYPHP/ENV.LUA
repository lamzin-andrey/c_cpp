local function getScriptPath()
    -- Получаем информацию о функции на 1-м уровне стека (текущая)
    local info = debug.getinfo(1, "S")
    -- Поле source содержит имя файла с префиксом '@'
    return info.source
end

local function getScriptDir()
    local path = getScriptPath()
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
