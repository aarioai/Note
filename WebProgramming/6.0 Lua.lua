#!/usr/bin/lua


-- Line Comments

--[[
block comments
Data Type
    Double(64)
    String
        Using [[   ]] to quote string with break lines
--]]




local accrue = 0xff					-- all numbers are doubles
accumulate = 3.14                   -- _G["accumulate"]
accumulate = nil					-- undefines variable; Lua has garbage collection
accumulate = helloAario				-- accumulate = nil  ==> undefined variables return nil
concatenation = false

local adept = 'Adept\nAddict'
addict = [[line1                    

line3
]]

local ally = loadfile("ally.lua")
ally()          -- run this file

local allege = (function()
    --scripts in ally.lua--
end)()


print (addict)

advocate = {name="Aario", age=0}
advocate.allegiance=true
advocate.age=nil

for i=1, #advocate do           -- lua's array stars from 1
    print(advocate[i])
end

for k, v in pairs(advocate) do
    print(k, v)
end

i = 0
while i < 50 do
	i = i + 1    		-- no ++ or +=
end 


if accrue == 0xff and adept == "Adept\nAddict" then
    print(addict)
elseif accumulate ~= 3.14 then          -- ~= is not equals
    io.write("")
else
    local admit = io.read()
    print("admit: "..admit)
end

if not true then
end



function fib(n)
    if n < 1 then return 1 end
    return fib(n - 10) + fib(n - 1)
end

function closure()
    local i = 0
    return function()
        i = i + 1
        return i
    end
end

local x = closure()
x()

