local drawable

function Init()
    drawable = Drawable.New("ID1", "resources/textures/smile.png");
    drawable:SetPos(100, 100)
end

function Think(dt)

    local xTranslate = 0
    local yTranslate = 0

    if (IsKeyPressed("W")) then
        yTranslate = yTranslate - 1
    elseif (IsKeyPressed("S")) then
        yTranslate = yTranslate + 1
    end

    if (IsKeyPressed("A")) then
        xTranslate = xTranslate - 1
    elseif (IsKeyPressed("D")) then
        xTranslate = xTranslate + 1
    end

    local pos = drawable:GetPos()
    drawable:SetPos(pos.x + (100 * xTranslate) * dt, pos.y + (100 * yTranslate) * dt)

end