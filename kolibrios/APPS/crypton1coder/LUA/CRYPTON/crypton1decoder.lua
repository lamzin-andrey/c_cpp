local php = dofile("/sd0/1/LIVES/KOLIBRI/HDATA/CODING/C/lldProject/APPS/crypton1coder/LUA/CRYPTON/DUMMYPHP/DUMMYPHP.LUA")
local LandCrypton = dofile("/sd0/1/LIVES/KOLIBRI/HDATA/CODING/C/lldProject/APPS/crypton1coder/LUA/CRYPTON/CRYPTON.LUA")

local __DIR__ = php.__DIR__(php.__FILE__(debug.getinfo(1, "S")))

php.echo("DIR = ", __DIR__ .. "pass.txt", "\n")

local pass =  php.file_get_contents(__DIR__ .. "pass.txt")
local s = php.file_get_contents(__DIR__ .. "input.txt")
os.remove(__DIR__ .. "pass.txt")
os.remove(__DIR__ .. "input.txt")

local cdata = LandCrypton:decrypt(s, pass)
php.file_put_contents(__DIR__ .. "output.txt", cdata)

php.echo("Done\n")

