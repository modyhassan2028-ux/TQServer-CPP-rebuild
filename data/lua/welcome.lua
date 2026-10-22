-- sample scripted NPC: on_talk is called when the player talks to the NPC
function on_talk()
    say("Welcome, adventurer! The Lua script engine is alive.")
    say("You are level " .. get_level() .. " carrying " .. get_money() .. " silver.")
    local r = rand(1, 6)
    if r == 6 then
        say("Lucky roll! Take this gift.")
        give_item(721258, 1)   -- meteorTea consumable from cq_itemtype
    else
        say("You rolled a " .. r .. ". Try talking to me again!")
    end
end
