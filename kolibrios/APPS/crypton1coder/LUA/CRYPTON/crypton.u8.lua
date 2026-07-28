-- LandCrypton для Lua 5.2 (KolibriOS)
-- Все строки в однобайтной кодировке (CP1251)

local LandCrypton = {}
LandCrypton.__index = LandCrypton

-- Константы
LandCrypton.WORK_ENCODING = "UTF-8"  -- Для совместимости, но в KolibriOS используем CP1251
LandCrypton.CP1251 = "WINDOWS-1251"
LandCrypton.CRYPTON_FW = "UTF-8"     -- Маркер начала строки

-- Состояние
LandCrypton.abcIsInitialized = false
LandCrypton.Map = {}

-- Вспомогательная функция для поиска в массиве
function LandCrypton:arrIndexOf(arr, value)
    for i, v in ipairs(arr) do
        if v == value then
            return i - 1  -- Возвращаем 0-индекс как в PHP
        end
    end
    return -1
end

-- Проверка пароля
function LandCrypton:validPassword(password, abc)
    for i = 1, #password do
        local ch = password:sub(i, i)
        if not abc:find(ch, 1, true) then
            return false
        end
    end
    return true
end

-- Получение лимитов для N-символов
function LandCrypton:getLimitN(d)
    local e = {9, 125, 1025, 1103}
    if d > e[1] and d < e[2] then
        return e[2], e[1]  -- L, b
    elseif d >= e[3] and d <= e[4] then
        return e[4], e[3]  -- L, b
    else
        return 2147483647, 0  -- PHP_INT_MAX
    end
end

-- Получение лимитов
function LandCrypton:getLimit(a, ctx, isN)
    if isN and isN == 1 then
        local L, b = self:getLimitN(a)
        ctx.L = L
        ctx.b = b
        return L
    end
    ctx.L = #ctx.abc
    ctx.b = 1
    return ctx.L
end

-- Получение кода символа
function LandCrypton:charCode(str, pos, ctx)
    local ch = str:sub(pos + 1, pos + 1)  -- pos - 0-based index
    local idx = ctx.abc:find(ch, 1, true)

    if idx then
        -- idx в Lua 1-based, в PHP 0-based
        local e = ctx.m[idx]  -- idx уже 1-based, m тоже 1-based
        return tostring(e)  -- e уже в 0-based индексации
    end

    -- Символ не найден в алфавите, возвращаем его код
    return "n" .. string.byte(ch)
end

-- Преобразование из кода в символ
function LandCrypton:fromCharCode(code, isN, ctx)
    if isN and isN == 1 then
        return string.char(code)
    end

    -- В PHP: d = arrIndexOf(m, e - 1), return abc[d]
    -- e в PHP - 1-based, поэтому e-1 - 0-based
    -- В Lua мы храним m как 1-based массив индексов
    local idx = code  -- code уже в 0-based, но нам нужен 1-based для поиска
    for i, v in ipairs(ctx.m) do
        if v == idx then  -- v уже в 0-based формате
            return ctx.abc:sub(i, i)
        end
    end
    return ""
end

-- Инициализация алфавита
function LandCrypton:initAbc(password, ctx)
    local abc = "012 3456789\n\r?!,.абвгдеёжзийклмнопрстуфхцчшщъыьэюяЙЦУКЕНГФЫВАПРОЛДЖЭЯЧСМИТЬБЮШЩЗХЪasdfghjklzxcvbnm-+qwertyuiopZXCVBNMASDFGHJKLQWERTYUIOP():/`=*[];'\t~@#$%^&_{}|\"<>"
    -- В KolibriOS строки уже в CP1251, просто используем как есть

    if self.abcIsInitialized then
        ctx.abc = abc
        ctx.m = self.Map
        return
    end

    if not self:validPassword(password, abc) then
        error("Invalid password")
    end

    local sz = #abc
    local c = {}
    for i = 1, sz do
        c[i] = i - 1  -- 0-based индексы
    end

    local e = 1  -- 1-based для обхода пароля
    for g = 1, sz do
        if e > #password then
            e = 1
        end
        local ch = password:sub(e, e)
        local di = abc:find(ch, 1, true)
        if not di then
            error("Invalid character in password")
        end
        -- di - 1-based, c работает с 0-based
        local dI = c[di]
        local I = c[g]
        local l = I + dI
        local maxIdx = #abc - 1
        if l > maxIdx then
            l = l - #abc
        end
        local d = self:arrIndexOf(c, l)
        c[g] = l
        c[d + 1] = I  -- d+1 потому что arrIndexOf возвращает 0-based
        e = e + 1
    end

    ctx.abc = abc
    self.Map = c
    ctx.m = c
    self.abcIsInitialized = true
end

-- Основной метод шифрования
function LandCrypton:crypt(s, password)
    password = password or ""
    local t = self.CRYPTON_FW .. s
    -- В KolibriOS все строки уже в CP1251, конвертация не нужна
    -- t = convertToCP1251(t) если нужно

    local c = password
    local f = 1  -- 1-based для обхода пароля
    local a = {}
    local q = {}

    self:initAbc(c, q)

    for h = 1, #t do
        if f > #c then
            f = 1
        end

        local o = self:charCode(t, h - 1, q)  -- h-1 для 0-based индекса
        local isN = 0
        if o:sub(1, 1) == "n" then
            isN = 1
            o = o:sub(2)
        end
        o = tonumber(o) or 0

        local e = self:charCode(c, f - 1, q)
        e = e:gsub("^n", "")
        e = tonumber(e) or 0

        local d = o + e
        self:getLimit(d, q, isN)
        local k = q.L
        local n = q.b

        if d > k then
            o = n + d - k
        else
            o = d
        end

        if isN == 1 then
            o = "n" .. tostring(o)
        end

        table.insert(a, tostring(o))
        f = f + 1
    end

    return table.concat(a, ";")
end

-- Внутренний метод расшифровки
function LandCrypton:_decrypt(encrypted, password)
    password = password or ""
    local t = {}
    for part in string.gmatch(encrypted, "[^;]+") do
        table.insert(t, part)
    end

    local c = password
    local f = 1
    local result = ""
    local q = {}

    self:initAbc(c, q)

    for h = 1, #t do
        if f > #c then
            f = 1
        end

        local e = self:charCode(c, f - 1, q)
        e = e:gsub("^n", "")
        e = tonumber(e) or 0

        local o = t[h]
        local isN = 0
        if o:sub(1, 1) == "n" then
            isN = 1
            o = o:sub(2)
        end
        o = tonumber(o) or 0

        local d = o - e
        local k = self:getLimit(o, q, isN)
        local n = q.b

        if d < n then
            d = k - math.abs(d - n)
            o = d
        else
            o = d
        end

        local char = self:fromCharCode(o, isN, q)
        result = result .. char
        f = f + 1
    end

    return result
end

-- Публичный метод расшифровки
function LandCrypton:decrypt(encrypted, password)
    password = password or ""
    local s = self:_decrypt(encrypted, password)

    if s:sub(1, #self.CRYPTON_FW) ~= self.CRYPTON_FW then
        error("Error decode!\n" .. s)
    end

    s = s:sub(#self.CRYPTON_FW + 1)
    return s
end

-- Функция для записи в файл (аналог echo)
function LandCrypton:writeToFile(filename, content, mode)
    mode = mode or "w"
    local file = io.open(filename, mode)
    if not file then
        error("Cannot open file: " .. filename)
    end
    file:write(content)
    file:close()
end

-- Тест
local function test()
    local s = "Как делишки!"
    local pass = "1Io01545"

    print("Исходная строка:", s)
    print("Пароль:", pass)

    -- Шифрование
    local cr = LandCrypton:crypt(s, pass)
    print("Зашифровано:", cr)

    -- Запись в файл
    LandCrypton:writeToFile("encrypted.txt", cr .. "\n\n")

    -- Расшифровка
    local de = LandCrypton:decrypt(cr, pass)
    print("Расшифровано:", de)

    -- Запись результата
    LandCrypton:writeToFile("result.txt", de .. "\n")

    return de
end

-- Запуск теста
test()

-- Возвращаем модуль для использования
return LandCrypton
