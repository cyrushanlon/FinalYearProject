

function createObject(tex,x,y,id)
    local obj = {}

    obj.drawable = DrawableComponent.New()
    obj.drawable:SetTexture(tex)
    obj.drawable:SetPos(x,y)

    obj.entity = Entity.New(id)
    obj.entity:AddDrawable(obj.drawable)
    
    return obj
end

function moveRelative(obj,x,y)
    startPos = obj.drawable:GetPos()
    obj.drawable:SetPos(startPos.x+x,startPos.y+y)
end

function turnAbs(obj,arg)
    obj.drawable:SetAng(arg)
end

function walk(obj, dir)
    oldAng = obj.drawable:GetAng()
    if dirTab[dir][3] == oldAng then
        moveRelative(obj,dirTab[dir][1],dirTab[dir][2])
    else
        turnAbs(obj, dirTab[dir][3])
    end
end

function HookKeyPressed(key)
    if (key == "W") then
        walk(player, 'north')
    elseif (key == "S") then
        walk(player, 'south')
    elseif (key == "A") then
        walk(player, 'west')
    elseif (key == "D") then
        walk(player, 'east')
    end
    
    if math.random() < 0.2 then
        enemies[#enemies+1] = createObject('./resources/textures/zomb.png',math.random()*1280,math.random()*720, 'enemy'..#enemies+1)
    end
    
    for i, enemy in pairs(enemies) do        
        local dirs = {'north', 'east', 'south', 'west'}
        walk(enemy, dirs[math.random(4)])     
    end
        
    
    
    --box:SetAng(0)
end

function Init()
    player = createObject('./resources/textures/arrow.png',50,100,'player')
    playerBearing = 'north'
    step=30
    
    enemies = {}
    
    dirTab = {}
    dirTab['north'] = {    0, -step,    0}
    dirTab['south'] = {    0,  step,  180}
    dirTab['east']  = { step,     0,   90} 
    dirTab['west']  = {-step,      0, 270}
end

function Think(dt)

end

