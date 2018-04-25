settings = {
    gravityY = -15,
	bgColor = 0xb93bcffff
}

math.randomseed( os.time() )

local floorBox = {}
local player = {}
local target = {}
local ents = {}
local toDelete = {}
local wall = {}
local toBreak = {}
local healthEnum = {}
local draggedEnt = nil
local score = 0
local jumpPower = 0
local shootPower = 0
local shooting = false
healthEnum[0.5] = 0
healthEnum[1] = 2
healthEnum[2] = 4
healthEnum[3] = 6
healthEnum[4] = 8

local entCount = 0;	

local mainView = Window.GetDefaultView()
local viewCoords = {
	x = 0,
	y = -650
}

local text = Text.New()
text:SetPos(10,-180)
text:SetColor(0,0,0,255)
text:SetString("Score: 0")

local shootSound = Sound.New("sshoot", "resources/sounds/ping_pong_8bit_beep_wall.wav")
local scoreSound = Sound.New("sscore", "resources/sounds/ping_pong_8bit_beep_paddle.wav")
local rockSounds = {
	Sound.New("s1", "resources/sounds/rock1.wav"),
	Sound.New("s2", "resources/sounds/rock2.wav"),
	Sound.New("s3", "resources/sounds/rock3.wav"),
	Sound.New("s4", "resources/sounds/rock4.wav"),
	Sound.New("s5", "resources/sounds/rock5.wav"),
	Sound.New("s6", "resources/sounds/rock6.wav"),
	Sound.New("s7", "resources/sounds/rock7.wav"),
	Sound.New("s8", "resources/sounds/rock8.wav")
}

function Init()
    settings.windowSize = Window.GetSize()
    mainView:Move(0, -650)
    mainView:Zoom(1)
	
    --floorBox wall
    floorBox.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active= true,
            type = "kinematic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 1,
        }),
        100, 10)
    floorBox.drawable = DrawableComponent.New()
    floorBox.drawable:SetTexture("resources/textures/quarry/floor.png")
    floorBox.entity = Entity.New("w1")
    floorBox.entity:AddPhysics(floorBox.physics)
    floorBox.entity:AddDrawable(floorBox.drawable)
    floorBox.physics:SetPos(50, -5)
	
    player.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active = true,
            type = "dynamic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 0.2,
            restitution = 0.3
        }),
        1, 1)
		
	player.drawable = DrawableComponent.New()
    player.drawable:SetTexture("resources/textures/head.png")
    player.entity = Entity.New("p")
    player.entity:AddPhysics(player.physics)
    player.entity:AddDrawable(player.drawable)
	player.physics:SetPos(5,3)
	
	target.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active = true,
            type = "kinematic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 0.2,
            restitution = 0
        }),
        4, 4)
	target.drawable = DrawableComponent.New()
    target.drawable:SetTexture("resources/textures/quarry/target.png")
    target.entity = Entity.New("t")
    target.entity:AddPhysics(target.physics)
    target.entity:AddDrawable(target.drawable)
	target.physics:SetPos(2,2)
	target.type = 'T'
	
	wall.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active = true,
            type = "kinematic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 0.2,
            restitution = 0
        }),
        0, 40)
    wall.entity = Entity.New("w2")
    wall.entity:AddPhysics(wall.physics)
	wall.physics:SetPos(0,20)
	wall.type = 'T'
	
	for y = 1, 4 do 
		local x = 0;
		for i=1, 12 do
			local size = math.random(4)
			x = x + size;
			createRock(x+35, 1+y*size,size, math.random() * 2 * math.pi, false)
		end
	end
end

function Think(dt)
    local xMove = 0
    local yMove = 0

    local zoom = 1

    -- if (IsKeyPressed("D")) then
        -- xMove = xMove + 1000
    -- end
    -- if (IsKeyPressed("A")) then
        -- xMove = xMove - 1000
    -- end
    -- if (IsKeyPressed("W")) then
        -- yMove = yMove - 1000
    -- end
    -- if (IsKeyPressed("S")) then
        -- yMove = yMove + 1000
    -- end

    -- if (IsKeyPressed("LControl")) then
        -- zoom = zoom - (0.5 * dt)
    -- end
    -- if (IsKeyPressed("LShift")) then
        -- zoom = zoom + (0.5 * dt)
    -- end
	
	xMove = (player.physics:GetPos().x*32 - viewCoords.x - 440)*5
	yMove = (player.physics:GetPos().y*-32 - viewCoords.y - 550)*5
    mainView:Move(xMove * dt, yMove * dt)
	viewCoords.x = viewCoords.x + xMove * dt
	viewCoords.y = viewCoords.y + yMove * dt
    mainView:Zoom(zoom)
	
	if (IsKeyPressed("A")) then
		if (player.physics:GetVel().x > -12) then
		player.physics:ApplyImpulse(-0.1, 0, true)
		end
    end
    if (IsKeyPressed("D")) then
		if (player.physics:GetVel().x < 12) then
			player.physics:ApplyImpulse(0.1, 0, true)
		end
    end
		
	for k,v in pairs(toDelete) do 
		deleteEnt(v)
		toDelete[k] = nil
	end
		
	for k,v in pairs(toBreak) do 
		breakRock(v)
		toBreak[k] = nil
	end
	
	if (draggedEnt ~= nil) then
		local mPos = getActualMousePos()
		local ePos = draggedEnt.physics:GetPos()
		local rPos = {
			x = mPos.x - ePos.x,
			y = mPos.y - ePos.y
		}
		local dist = distance(mPos.x, mPos.y, ePos.x, ePos.y)

		local playerDistance = distance(player.physics:GetPos().x, player.physics:GetPos().y, mPos.x, mPos.y)
		if (playerDistance > 10) then
			endDrag()
		else
			draggedEnt.physics:ApplyImpulse(rPos.x/dist/10, rPos.y/dist/10, true)
		end
	end
	
	if (jumpPower < 1) then
		jumpPower = jumpPower + dt
	end
	if (shootPower < 0.2) then
		shootPower = shootPower + dt
	elseif (shooting) then
		shoot()
		shootPower = 0
	end
	
	text:SetString("Score: " .. score)
end

-----------------------------------------------------------------------
-- Hooks
-----------------------------------------------------------------------
function HookMousePressed(isLeft)
	if (isLeft) then
		shooting = true
	else	
		startDrag()
	end
end

function HookMouseReleased(isLeft)
	if (isLeft) then
		shooting = false
	else
		endDrag()
	end
end

function HookBeginContact(a, b)
	local aEnt = ents[tonumber(a)]
	local bEnt = ents[tonumber(b)]	
	if (aEnt and aEnt.type == 'B') then
		impactBullet(aEnt, b)
	elseif (bEnt and bEnt.type == 'B') then
		impactBullet(bEnt, a)
	elseif (a == 't') then
		impactCollector(b)
	elseif (b == 't') then
		impactCollector(a)
	else
		return
	end
end

function HookEndContact(a, b)
    --print("end " .. a .. " " .. b)
end

function HookKeyPressed(key)
    if (key == "Space" and jumpPower > 1) then
		player.physics:ApplyImpulse(0, 10, true)
		jumpPower = 0
	end
end

-----------------------------------------------------------------------
-- Functions
-----------------------------------------------------------------------
function createRock(x, y, size, ang, center)
	local rock = {}
	local texture = math.floor(size)
	
	if (size == 0.5) then
		if (math.random(10) == 1) then
			texture = 'gold'
		else
			texture = 'quarter'
		end
	end
	
	-- Entity reuse
	for k,v in pairs(ents) do
		if (v.deleted and v.type == 'R' and v.size == size and v.gold == (texture == 'gold')) then
			rock = v
			rock.physics:SetActive(true)
			rock.physics:SetAngVel(0)
			break;
		end
	end
	
	if (not rock.id) then
		local id = entCount
		entCount = entCount+1
		rock.drawable = DrawableComponent.New()
		rock.drawable:SetTexture("resources/textures/quarry/rock"..texture..".png")
		rock.physics = PhysicsComponent.New(
			b2BodyDef.New({
				active = true,
				type = "dynamic"
			}),
			b2FixtureDef.New({
				density = 1,
				friction= 1,
				restitution = 0
			}),
			size, size)
		rock.entity = Entity.New(id)		
		rock.entity:AddDrawable(rock.drawable)
		rock.entity:AddPhysics(rock.physics)
		rock.id = id
		rock.type = 'R'
		if (texture == 'gold') then
			rock.gold = true
		else 
			rock.gold = false
		end
		ents[id] = rock
	end
	
	if (center) then
		rock.physics:SetPos(x, y)
	else 
		rock.physics:SetPos(x-size/2,y-size/2)
	end
	rock.physics:SetVel(0,0)
	rock.physics:SetAng(ang)
	rock.size = size
	rock.deleted = false
	rock.health = size
end

function shoot()
	local pPos = player.physics:GetPos()
	local mPos = getActualMousePos()
	local rPos = {
		x = mPos.x - pPos.x,
		y = mPos.y - pPos.y
	}
	local dist = pythagoran(rPos)
	
	local bullet = {}	
	-- Entity reuse
	for k,v in pairs(ents) do
		if (v.deleted and v.type == 'B') then
			bullet = v
			v.physics:SetActive(true)
			v.physics:SetAngVel(0)
			break;
		end
	end

	if (not bullet.id) then
		local id = entCount
		entCount = entCount + 1
		bullet.drawable = DrawableComponent.New()
		bullet.drawable:SetTexture("resources/textures/quarry/bullet.png")
		bullet.physics = PhysicsComponent.New(
			b2BodyDef.New({
				active = true,
				type = "dynamic",
				bullet = true
			}),
			b2FixtureDef.New({
				density = 5,
				friction= 1,
				restitution = 0
			}),
			0.5, 0.5)
		bullet.entity = Entity.New(id)		
		bullet.entity:AddDrawable(bullet.drawable)
		bullet.entity:AddPhysics(bullet.physics)
		bullet.id = id
		bullet.type = 'B'
		ents[id] = bullet
	end
	bullet.physics:SetPos(
		pPos.x-0.25+rPos.x/dist*1.5,
		pPos.y-0.25+rPos.y/dist*1.5
	)
	bullet.physics:SetVel(
		rPos.x/dist*100,
		rPos.y/dist*100
	)
	bullet.physics:SetAng(0)
	bullet.deleted = false
	shootSound:Play()
end

function deleteEnt(ent)
	ent.physics:SetPos(9999,-9999)
	ent.deleted = true
	ent.physics:SetActive(false)
end

function breakRock(rock)
	if (rock.size < 1) then
		deleteEnt(rock)
		return
	end
	
	rockSounds[math.random(#rockSounds)]:Play()

	if (rock.size == 3) then
		local ang = rock.physics:GetAng()
		local rbig = 0.5  --math.sqrt(rock.size/6 * rock.size/6 + rock.size/6 * rock.size/6)
		local redge = 1 --math.sqrt(1 * 1 + 0 * 1)
		local rcorner = math.sqrt(2) --math.sqrt(1 * 1 + 1 * 1)

		--Big rock
		local pos = angleToPos(ang + math.pi * 1 / 4, rbig)
		createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, 2, ang + math.random(4)*math.pi/2, true)
		--Edge rocks (2)
		local pos = angleToPos(ang + math.pi, redge)
		createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, 1, ang + math.random(4)*math.pi/2, true)
		local pos = angleToPos(ang + math.pi * 3 / 2, redge)
		createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, 1, ang + math.random(4)*math.pi/2, true)
		--Corner rocks (3)
		local pos = angleToPos(ang + math.pi * 3 / 4, rcorner)
		createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, 1, ang + math.random(4)*math.pi/2, true)
		local pos = angleToPos(ang + math.pi * 5 / 4, rcorner)
		createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, 1, ang + math.random(4)*math.pi/2, true)
		local pos = angleToPos(ang + math.pi * 7 / 4, rcorner)
		createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, 1, ang + math.random(4)*math.pi/2, true)
		
		deleteEnt(rock)
		
		return
	end
	
	-- Rock sizes 1 2 and 4:
	local ang = rock.physics:GetAng()
	local r = rock.size/4 * rock.size/4
	
	local pos = angleToPos(ang + math.pi * 1 / 4, r)
	createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, rock.size/2, ang + math.random(4)*math.pi/2, true)
	local pos = angleToPos(ang + math.pi * 3 / 4, r)
	createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, rock.size/2, ang + math.random(4)*math.pi/2, true)
	local pos = angleToPos(ang + math.pi * 5 / 4, r)
	createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, rock.size/2, ang + math.random(4)*math.pi/2, true)
	local pos = angleToPos(ang + math.pi * 7 / 4, r)
	createRock(pos.x + rock.physics:GetPos().x, pos.y  + rock.physics:GetPos().y, rock.size/2, ang + math.random(4)*math.pi/2, true)
	
	deleteEnt(rock)
end

function angleToPos(angle, r)
	local pos = {
		x = math.sin(angle)*r,
		y = math.cos(angle)*r
	}
	
	return pos
end

function pythagoran(object)
	return math.sqrt(object.x * object.x + object.y * object.y)
end

function impactBullet(bullet, entId)
	local ent = ents[tonumber(entId)]
	if (ent and ent.type == 'R')	then
		ent.health = ent.health - 1
		if (ent.health <= 0) then
			table.insert(toBreak, ent)
		end
	elseif (ent and ent.type == 'B') then
		table.insert(toDelete, ent)
	end
	
	if (ent and ent.type == 'R' and ent.size == 0.5) then
	else
		table.insert(toDelete, bullet)
	end
end

function findInRadius(x, y, r)
	local found = {}
    for k,v in pairs(ents) do
        local pos = v.physics:GetPos()
        if (pos.x > x-r and pos.x < x+r and pos.y > y-r and pos.y < y+r) then
            if (r*r > (pos.x-x)^2 + (pos.y-y)^2) then
				--found[k] = v
				return v
            end
        end
    end
	--return found
end
 
function distance(x, y, x2, y2)
    return math.sqrt((x-x2)^2+(y-y2)^2)
end

function getActualMousePos()
	return {	
		x = (GetMousePos().x + viewCoords.x) / 32,
		y = (GetMousePos().y + viewCoords.y) / -32
	}
end

-- Dragging

function startDrag()
	local mPos = getActualMousePos()
	local found = findInRadius(mPos.x, mPos.y, 1)

	if (found ~= nil) then
		draggedEnt = found
	end
end

function endDrag()
	draggedEnt = nil
end

-- ijawdhikwuyd games almost done :D
function impactCollector(entId)
	local ent = ents[tonumber(entId)]
	if (ent and ent.type == 'R')then
		if (ent.gold) then
			score = score + 1
			scoreSound:Play()
		end
		table.insert(toDelete, ent)
	end
end