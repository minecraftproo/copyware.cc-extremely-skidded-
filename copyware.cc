local library31 = loadstring(game:HttpGet("https://raw.githubusercontent.com/dwa31/lua/main/utaniyorum"))()

-- Aimlock Settings

getgenv().AimPart = "HumanoidRootPart" -- For R15 Games: {UpperTorso, LowerTorso, HumanoidRootPart, Head} | For R6 Games: {Head, Torso, HumanoidRootPart}
getgenv().AimlockKey = "q"
getgenv().AimRadius = 30 -- How far away from someones character you want to lock on at
getgenv().ThirdPerson = true 
getgenv().FirstPerson = true
getgenv().TeamCheck = false -- Check if Target is on your Team (True means it wont lock onto your teamates, false is vice versa) (Set it to false if there are no teams)
getgenv().PredictMovement = true -- Predicts if they are moving in fast velocity (like jumping) so the aimbot will go a bit faster to match their speed 
getgenv().PredictionVelocity = 3.372
getgenv().OldAimPart = "HumanoidRootPart"
getgenv().CheckIfJumped = true
getgenv().Multiplier = -0.27


local Config = {
    WindowName = "copyware.cc private premium",
	Color = Color3.fromRGB(255,0,255),
	Keybind = Enum.KeyCode.RightShift
}

local Library = loadstring(game:HttpGet("https://raw.githubusercontent.com/AlexR32/Roblox/main/BracketV3.lua"))()
local Window = Library:CreateWindow(Config, game:GetService("CoreGui"))

Window:SetBackground("2151741365")

local Tab1 = Window:CreateTab("Legit")
local Tab2 = Window:CreateTab("Rage")
local Tab3 = Window:CreateTab("Misc")
local Tab4 = Window:CreateTab("Target")

-- Fucking Aimlock

repeat wait() until game:IsLoaded()

getgenv().Aimlock = false

local Players, Uis, RService, SGui = game:GetService"Players", game:GetService"UserInputService", game:GetService"RunService", game:GetService"StarterGui";
local Client, Mouse, Camera, CF, RNew, Vec3, Vec2 = Players.LocalPlayer, Players.LocalPlayer:GetMouse(), workspace.CurrentCamera, CFrame.new, Ray.new, Vector3.new, Vector2.new;
local MousePressed, CanNotify = false, false;
local AimlockTarget;
local OldPre;

getgenv().CiazwareUniversalAimbotLoaded = true

getgenv().WorldToViewportPoint = function(P)
	return Camera:WorldToViewportPoint(P)
end

getgenv().WorldToScreenPoint = function(P)
	return Camera.WorldToScreenPoint(Camera, P)
end

getgenv().GetObscuringObjects = function(T)
	if T and T:FindFirstChild(getgenv().AimPart) and Client and Client.Character:FindFirstChild("Head") then 
		local RayPos = workspace:FindPartOnRay(RNew(
			T[getgenv().AimPart].Position, Client.Character.Head.Position)
		)
		if RayPos then return RayPos:IsDescendantOf(T) end
	end
end

getgenv().GetNearestTarget = function()
	-- Credits to whoever made this, i didnt make it, and my own mouse2plr function kinda sucks
	local players = {}
	local PLAYER_HOLD  = {}
	local DISTANCES = {}
	for i, v in pairs(Players:GetPlayers()) do
		if v ~= Client then
			table.insert(players, v)
		end
	end
	for i, v in pairs(players) do
		if v.Character ~= nil then
			local AIM = v.Character:FindFirstChild("Head")
			if getgenv().TeamCheck == true and v.Team ~= Client.Team then
				local DISTANCE = (v.Character:FindFirstChild("Head").Position - game.Workspace.CurrentCamera.CFrame.p).magnitude
				local RAY = Ray.new(game.Workspace.CurrentCamera.CFrame.p, (Mouse.Hit.p - game.Workspace.CurrentCamera.CFrame.p).unit * DISTANCE)
				local HIT,POS = game.Workspace:FindPartOnRay(RAY, game.Workspace)
				local DIFF = math.floor((POS - AIM.Position).magnitude)
				PLAYER_HOLD[v.Name .. i] = {}
				PLAYER_HOLD[v.Name .. i].dist= DISTANCE
				PLAYER_HOLD[v.Name .. i].plr = v
				PLAYER_HOLD[v.Name .. i].diff = DIFF
				table.insert(DISTANCES, DIFF)
			elseif getgenv().TeamCheck == false and v.Team == Client.Team then 
				local DISTANCE = (v.Character:FindFirstChild("Head").Position - game.Workspace.CurrentCamera.CFrame.p).magnitude
				local RAY = Ray.new(game.Workspace.CurrentCamera.CFrame.p, (Mouse.Hit.p - game.Workspace.CurrentCamera.CFrame.p).unit * DISTANCE)
				local HIT,POS = game.Workspace:FindPartOnRay(RAY, game.Workspace)
				local DIFF = math.floor((POS - AIM.Position).magnitude)
				PLAYER_HOLD[v.Name .. i] = {}
				PLAYER_HOLD[v.Name .. i].dist= DISTANCE
				PLAYER_HOLD[v.Name .. i].plr = v
				PLAYER_HOLD[v.Name .. i].diff = DIFF
				table.insert(DISTANCES, DIFF)
			end
		end
	end
	
	if unpack(DISTANCES) == nil then
		return nil
	end
	
	local L_DISTANCE = math.floor(math.min(unpack(DISTANCES)))
	if L_DISTANCE > getgenv().AimRadius then
		return nil
	end
	
	for i, v in pairs(PLAYER_HOLD) do
		if v.diff == L_DISTANCE then
			return v.plr
		end
	end
	return nil
end

Mouse.KeyDown:Connect(function(a)
	if not (Uis:GetFocusedTextBox()) then 
		if a == AimlockKey and AimlockTarget == nil then
			pcall(function()
				if MousePressed ~= true then MousePressed = true end 
				local Target;Target = GetNearestTarget()
				if Target ~= nil then 
					AimlockTarget = Target
				end
			end)
		elseif a == AimlockKey and AimlockTarget ~= nil then
			if AimlockTarget ~= nil then AimlockTarget = nil end
			if MousePressed ~= false then 
				MousePressed = false 
			end
		end
	end
end)
RService.RenderStepped:Connect(function()
	local AimPartOld = getgenv().OldAimPart
	if getgenv().ThirdPerson == true and getgenv().FirstPerson == true then 
		if (Camera.Focus.p - Camera.CoordinateFrame.p).Magnitude > 1 or (Camera.Focus.p - Camera.CoordinateFrame.p).Magnitude <= 1 then 
			CanNotify = true 
		else 
			CanNotify = false 
		end
	elseif getgenv().ThirdPerson == true and getgenv().FirstPerson == false then 
		if (Camera.Focus.p - Camera.CoordinateFrame.p).Magnitude > 1 then 
			CanNotify = true 
		else 
			CanNotify = false 
		end
	elseif getgenv().ThirdPerson == false and getgenv().FirstPerson == true then 
		if (Camera.Focus.p - Camera.CoordinateFrame.p).Magnitude <= 1 then 
			CanNotify = true 
		else 
			CanNotify = false 
		end
	end
	if getgenv().Aimlock == true and MousePressed == true then 
		if AimlockTarget and AimlockTarget.Character and AimlockTarget.Character:FindFirstChild(getgenv().AimPart) then 
			if getgenv().FirstPerson == true then
				if CanNotify == true then
					if getgenv().PredictMovement == true then 
						Camera.CFrame = CF(Camera.CFrame.p, AimlockTarget.Character[getgenv().AimPart].Position + AimlockTarget.Character[getgenv().AimPart].Velocity/PredictionVelocity)
					elseif getgenv().PredictMovement == false then 
						Camera.CFrame = CF(Camera.CFrame.p, AimlockTarget.Character[getgenv().AimPart].Position)
					end
				end
			elseif getgenv().ThirdPerson == true then 
				if CanNotify == true then
					if getgenv().PredictMovement == true then 
						Camera.CFrame = CF(Camera.CFrame.p, AimlockTarget.Character[getgenv().AimPart].Position + AimlockTarget.Character[getgenv().AimPart].Velocity/PredictionVelocity)
					elseif getgenv().PredictMovement == false then 
						Camera.CFrame = CF(Camera.CFrame.p, AimlockTarget.Character[getgenv().AimPart].Position)
					end
				end 
			end
		end
	end
	if getgenv().CheckIfJumped == true then
		if AimlockTarget.Character.Humanoid.FloorMaterial == Enum.Material.Air and AimlockTarget.Character.Humanoid.Jump == true then
			getgenv().AimPart = "RightLowerLeg"
		else
			getgenv().AimPart = AimPartOld
		end
	end
end)

-- End Fucking Aimlock Function

-- Legit Section

local Section1 = Tab1:CreateSection("Aimbot")

local Toggle1 = Section1:CreateToggle("Enabled", nil, function(state)
	getgenv().Aimlock = not getgenv().Aimlock
end)

local Toggle2 = Section1:CreateToggle("Airshot function", nil, function(state)
	getgenv().CheckIfJumped = state
end)

local Dropdown1 = Section1:CreateDropdown("Bodypart", {"Head","UpperTorso","HumanoidRootPart","LowerTorso"}, function(objective)
	getgenv().AimPart = objective
	getgenv().OldAimPart = objective
end)

local Section2 = Tab1:CreateSection("Triggerbot")

local Toggle3 = Section2:CreateToggle("Enabled", nil, function(state)
	local player = game.Players.LocalPlayer
	local mouse = player:GetMouse()
	local Players = game:FindService("Players")

	if state == true then
		repeat wait()
			local target = mouse.Target	
				if target then
					if target.Parent:IsA("Model") then
						for i,v in pairs(Players:GetChildren()) do
							if v.Name == target.Parent.Name or v.Name == target.Parent.Parent.Name then
								mouse1click()
							end
						end
					end
				end
		until state == false
	end
end)

local Toggle4 = Section2:CreateToggle("Delay", nil, function()
		
end)

local TextBox1 = Section2:CreateTextBox("Set Delay", "", true, function()
	
end)

local Section3 = Tab1:CreateSection("Aimbot Settings")

local TextBox2 = Section3:CreateTextBox("Aim Prediction", "", true, function(a)
	getgenv().PredictionVelocity = tostring(a)
end)

local TextBox3167 = Section3:CreateTextBox("Aim radius", "", true, function(a)
	getgenv().AimRadius = tonumber(a)
end)

local TextBox3 = Section3:CreateTextBox("Aim Key", "", true, function(a)
	getgenv().AimlockKey = tonumber(a)
end)

-- Finish <3

-- Rage Section

local Section4 = Tab2:CreateSection("Silent Aim")

local Toggle5 = Section4:CreateToggle("Silent Aim", nil, function(saksoamaarkakoltukolan)
	local Aiming = loadstring(game:HttpGet("https://raw.githubusercontent.com/alingiaer/silenta/main/asd"))()
	Aiming.TeamCheck(false)
	
	local Workspace = game:GetService("Workspace")
	local Players = game:GetService("Players")
	local RunService = game:GetService("RunService")
	local UserInputService = game:GetService("UserInputService")
	
	local LocalPlayer = Players.LocalPlayer
	local Mouse = LocalPlayer:GetMouse()
	local CurrentCamera = Workspace.CurrentCamera
	
	local DaHoodSettings = {
		SilentAim = true,
		AimLock = false,
		AimLockKeybind = Enum.KeyCode.E
	}
	getgenv().DaHoodSettings = DaHoodSettings
	
	function Aiming.Check()
		if not (Aiming.Enabled == true and Aiming.Selected ~= LocalPlayer and Aiming.SelectedPart ~= nil) then
			return false
		end
	
		local Character = Aiming.Character(Aiming.Selected)
		local KOd = Character:WaitForChild("BodyEffects")["K.O"].Value
		local Grabbed = Character:FindFirstChild("GRABBING_CONSTRAINT") ~= nil
	
		if (KOd or Grabbed) then
			return false
		end
	
		return true
	end
	
	local __index
	__index = hookmetamethod(game, "__index", function(t, k)
		if (t:IsA("Mouse") and (k == "Hit" or k == "Target") and Aiming.Check()) then
			local SelectedPart = Aiming.SelectedPart
	
			if (DaHoodSettings.SilentAim and (k == "Hit" or k == "Target")) then
				local Hit = SelectedPart.CFrame + (SelectedPart.Velocity * DaHoodSettings.Prediction)
	
				return (k == "Hit" and Hit or SelectedPart)
			end
		end
	
		return __index(t, k)
	end)
	
	RunService:BindToRenderStep("AimLock", 0, function()
		if (DaHoodSettings.AimLock and Aiming.Check() and UserInputService:IsKeyDown(DaHoodSettings.AimLockKeybind)) then
			local SelectedPart = Aiming.SelectedPart
	
			local Hit = SelectedPart.CFrame + (SelectedPart.Velocity * DaHoodSettings.Prediction)
	
			CurrentCamera.CFrame = CFrame.lookAt(CurrentCamera.CFrame.Position, Hit.Position)
		end
		end)
    if saksoamaarkakoltukolan == false then
	Aiming.ShowFOV = false
    DaHoodSettings.Prediction = 0
    Aiming.FOV = 0
    end
end)

local Toggle7 = Section4:CreateToggle("Ping Based Prediction", nil, function()
	DaHoodSettings.Prediction = 0.420
end)

local Toggle8 = Section4:CreateToggle("Visible Check", nil, function(cuvalue)
	Aiming.VisibleCheck = cuvalue
end)

local Toggle9 = Section4:CreateToggle("Ignore FOV", nil, function()
	Aiming.ShowFOV = false
end)

local Dropdown4 = Section4:CreateDropdown("Hitbox", {"Head","UpperTorso","HumanoidRootPart","LowerTorso"}, function(L_73_arg0)
	getgenv().AimPart = L_73_arg0
end)

local Section5 = Tab2:CreateSection("FOV")

local Toggle10 = Section5:CreateToggle("Enabled", nil, function(L_75_arg0)
	Aiming.ShowFOV = L_75_arg0
end)

local Slider5 = Section5:CreateSlider("Size", 0,500,nil,true, function(L_74_arg0)
	Aiming.FOV = L_74_arg0
end)

local Colorpicker1 = Section5:CreateColorpicker("Color", function(Valuecolor)
	Aiming.FOVColour = Valuecolor
end)

-- Finish <3

local Section6 = Tab3:CreateSection("Movement")

local Button1234 = Section6:CreateButton("CFrame Fix", function()	
	for _, v in pairs(game.Players.LocalPlayer.Character:GetChildren()) do
		if v:IsA("Script") and v.Name ~= "Health" and v.Name ~= "Sound" and v:FindFirstChild("LocalScript") then
			v:Destroy()
		end
	end
	game.Players.LocalPlayer.CharacterAdded:Connect(function(char)
		repeat
			wait()
		until game.Players.LocalPlayer.Character
		char.ChildAdded:Connect(function(child)
			if child:IsA("Script") then 
				wait(0.1)
				if child:FindFirstChild("LocalScript") then
					child.LocalScript:FireServer()
				end
			end
		end)
	end)

end)

local glitch = false
local clicker = false

local TextBox24356 = Section6:CreateTextBox("CFrame", "", true, function(a)
	getgenv().Multiplier = a
end)

local Button12374 = Section6:CreateButton("CFrame (Z)", function()
	local userInput = game:service('UserInputService')
	local runService = game:service('RunService')
	
	userInput.InputBegan:connect(function(Key)
		if Key.KeyCode == Enum.KeyCode.Z then
			Enabled = not Enabled
			if Enabled == true then
				repeat
					game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame = game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame + game.Players.LocalPlayer.Character.Humanoid.MoveDirection * getgenv().Multiplier
					runService.Stepped:wait()
				until Enabled == false
			end
		end
	end)
end)

local Button92374 = Section6:CreateButton("Toggle Speed Glitch (X)", function()
	local Player = game:GetService("Players").LocalPlayer
	local Mouse = Player:GetMouse()
	local SpeedGlitch = false
	local Wallet = Player.Backpack:FindFirstChild("Wallet")

	local UniversalAnimation = Instance.new("Animation")

	function stopTracks()
		for _, v in next, game:GetService("Players").LocalPlayer.Character:FindFirstChildOfClass("Humanoid"):GetPlayingAnimationTracks() do
			if (v.Animation.AnimationId:match("rbxassetid")) then
				v:Stop()
			end
		end
	end

	function loadAnimation(id)
		if UniversalAnimation.AnimationId == id then
			stopTracks()
			UniversalAnimation.AnimationId = "1"
		else
			UniversalAnimation.AnimationId = id
			local animationTrack = game:GetService("Players").LocalPlayer.Character:FindFirstChildOfClass("Humanoid"):LoadAnimation(UniversalAnimation)
			animationTrack:Play()
		end
	end

	Mouse.KeyDown:Connect(function(Key)
		if Key == "x" then
			SpeedGlitch = not SpeedGlitch
			if SpeedGlitch == true then
				stopTracks()
				loadAnimation("rbxassetid://3189777795")
				wait(1.5)
				Wallet.Parent = Player.Character
				wait(0.15)
				Player.Character:FindFirstChild("Wallet").Parent = Player.Backpack
				wait(0.05)
				repeat game:GetService("RunService").Heartbeat:wait()
					keypress(0x49)
					game:GetService("RunService").Heartbeat:wait()
					keypress(0x4F)
					game:GetService("RunService").Heartbeat:wait()
					keyrelease(0x49)
					game:GetService("RunService").Heartbeat:wait()
					keyrelease(0x4F)
					game:GetService("RunService").Heartbeat:wait()
				until SpeedGlitch == false
			end
		end
	end)
end)

local Button99678074 = Section6:CreateButton("Toxic Message (K)", function()
    local plr = game.Players.LocalPlayer
repeat wait() until plr.Character
local char = plr.Character

local garbage = {
	"mad kid";
    "your getting rekted by .gg/insomniac.";
    "your sus.";
    "ez";
    "my grandma has more skill than you";
    "seed";
    "sit son";
    "trash";
    "LOL";
    "nn tapped, bad cheat.";
    ".gg/insomniac";
    "your sus.";
    "your getting rekted by .gg/insomniac.";
    "you lose";
    "nn tapped, bad cheat.";
    "leave";
    "no skill";
    "bad";
    "you're nothing";
    "so trash";
    "so bad";
    "ur salty";
    "salty";
    "cry more";
    "keep crying";
    "run 1s seed";
    "just quit";
    "lol ur aim buy insomniac";









}


function TrashTalk(inputObject, gameProcessedEvent)
    if inputObject.KeyCode == Enum.KeyCode.K and gameProcessedEvent == false then        
game.ReplicatedStorage.DefaultChatSystemChatEvents.SayMessageRequest:FireServer(
        garbage[math.random(1,#garbage)],
        "All"
    )
    end
end
 
game:GetService("UserInputService").InputBegan:connect(TrashTalk)
end)

local Button99074 = Section6:CreateButton("Auto Clicker (V)", function()
	local Player = game:GetService("Players").LocalPlayer
	local Mouse = Player:GetMouse()
	local Clicking = false
	Mouse.KeyDown:Connect(function(Key)
		if Key == "z" then
			Clicking = not Clicking
			if Clicking == true then
				repeat
					mouse1click()
					wait(0.001)
				until Clicking == false
			end
		end
	end)
end)

local Button1 = Section6:CreateButton("Anti-Slow", function()
	repeat
		wait()
	until game:IsLoaded()
	getgenv().Fix = true
	getgenv().TeclasWS = {
		["tecla1"] = "nil",
		["tecla2"] = "nil",
		["tecla3"] = "H"
	}
	local L_121_ = game:GetService("Players")
	local L_122_ = game:GetService("StarterGui") or "son una mierda"
	local L_123_ = L_121_.LocalPlayer
	local L_124_ = L_123_:GetMouse()
	local L_125_ = getrenv()._G
	local L_126_ = getrawmetatable(game)
	local L_127_ = L_126_.__newindex
	local L_128_ = L_126_.__index
	local L_129_ = 22
	local L_130_ = true
	function anunciar_atentado_terrorista(L_138_arg0)
		L_122_:SetCore("SendNotification", {
			Title = "anti lock fix",
			Text = L_138_arg0
		})
	end
	getgenv().TECHWAREWALKSPEED_LOADED = true
	wait(1.5)
	anunciar_atentado_terrorista("Press  " .. TeclasWS.tecla3 .. " to turn on/off anti lock fix")
	L_124_.KeyDown:Connect(
            function(L_139_arg0)
		if L_139_arg0:lower() == TeclasWS.tecla1:lower() then
			L_129_ = L_129_ + 1
			anunciar_atentado_terrorista("播放器速度已提高 (speed = " .. tostring(L_129_) .. ")")
		elseif L_139_arg0:lower() == TeclasWS.tecla2:lower() then
			L_129_ = L_129_ - 1
			anunciar_atentado_terrorista("玩家的速度已降低 (speed = " .. tostring(L_129_) .. ")")
		elseif L_139_arg0:lower() == TeclasWS.tecla3:lower() then
			if L_130_ then
				L_130_ = false
				anunciar_atentado_terrorista("anti lock fix off")
			else
				L_130_ = true
				anunciar_atentado_terrorista("anti lock fix on")
			end
		end
	end
        )
	setreadonly(L_126_, false)
	L_126_.__index =
            newcclosure(
            function(L_140_arg0, L_141_arg1)
		local L_142_ = checkcaller()
		if L_141_arg1 == "WalkSpeed" and not L_142_ then
			return L_125_.CurrentWS
		end
		return L_128_(L_140_arg0, L_141_arg1)
	end
        )
	L_126_.__newindex =
            newcclosure(
            function(L_143_arg0, L_144_arg1, L_145_arg2)
		local L_146_ = checkcaller()
		if L_130_ then
			if L_144_arg1 == "WalkSpeed" and L_145_arg2 ~= 0 and not L_146_ then
				return L_127_(L_143_arg0, L_144_arg1, L_129_)
			end
		end
		return L_127_(L_143_arg0, L_144_arg1, L_145_arg2)
	end
        )
	setreadonly(L_126_, true)
	repeat
		wait()
	until game:IsLoaded()
	local L_131_ = game:service("Players")
	local L_132_ = L_131_.LocalPlayer
	repeat
		wait()
	until L_132_.Character
	local L_133_ = game:service("UserInputService")
	local L_134_ = game:service("RunService")
	local L_135_ = -0.27
	local L_136_ = false
	local L_137_
	L_133_.InputBegan:connect(
            function(L_147_arg0)
		if L_147_arg0.KeyCode == Enum.KeyCode.LeftBracket then
			L_135_ = L_135_ + 0.01
			print(L_135_)
			wait(0.2)
			while L_133_:IsKeyDown(Enum.KeyCode.LeftBracket) do
				wait()
				L_135_ = L_135_ + 0.01
				print(L_135_)
			end
		end
		if L_147_arg0.KeyCode == Enum.KeyCode.RightBracket then
			L_135_ = L_135_ - 0.01
			print(L_135_)
			wait(0.2)
			while L_133_:IsKeyDown(Enum.KeyCode.RightBracket) do
				wait()
				L_135_ = L_135_ - 0.01
				print(L_135_)
			end
		end
		if L_147_arg0.KeyCode == Enum.KeyCode.Z then
			L_136_ = not L_136_
			if L_136_ == true then
				repeat
					game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame =
                                game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame +
                                game.Players.LocalPlayer.Character.Humanoid.MoveDirection * L_135_
					game:GetService("RunService").Stepped:wait()
				until L_136_ == false
			end
		end
	end)
end)

local Button2 = Section6:CreateButton("Fake Speed Glitch (Q)", function()
    mouse = game.Players.LocalPlayer:GetMouse()
down = false
local plr = game:GetService('Players').LocalPlayer

    function onButton1Down(mouse)
    down = true
    while down do
    if not down then break end
    local char = plr.Character
    
    char.HumanoidRootPart.Velocity = char.HumanoidRootPart.CFrame.lookVector * 250
    wait()
    end
    end
    
    function onButton1Up(mouse)
    down = false
    end
    
    function onSelected(mouse)
    mouse.KeyDown:connect(function(k) if k:lower()=="q"then onButton1Down(mouse)end end)
    mouse.KeyUp:connect(function(k) if k:lower()=="q"then onButton1Up(mouse)end end)
    end
    
    onSelected(game.Players.LocalPlayer:GetMouse())
end)


local Button5 = Section6:CreateButton("WalkSpeed", function()
--// Local Functions
local lp = game:GetService"Players".LocalPlayer
local SuperSpeed = Instance.new("IntValue",lp.Character.BodyEffects.Movement);SuperSpeed.Name = "SuperSpeed"
local HulkJump = Instance.new("IntValue",lp.Character.BodyEffects.Movement);HulkJump.Name = "HulkJump"
--// Local Functions

	if bodyeffects_folder.Movement:findFirstChild("SuperSpeed") then
		walkspeed = 300
		end
		if bodyeffects_folder.Movement:findFirstChild("HighJump") then
		jumppower = 30
		end
end)

-- Finish <3

local Section7 = Tab3:CreateSection("more")

local Toggle13 = Section7:CreateToggle("Auto Farm", nil, function(texto)
	repeat
		wait()
	until game:IsLoaded()
	local gm = getrawmetatable(game)
	setreadonly(gm, false)
	local namecall = gm.__namecall
	gm.__namecall =
		newcclosure(
		function(self, ...)
			local args = {...}
			if not checkcaller() and getnamecallmethod() == "FireServer" and tostring(self) == "MainEvent" then
				if tostring(getcallingscript()) ~= "Framework" then
					return
				end
			end
			if not checkcaller() and getnamecallmethod() == "Kick" then
				return
			end
			return namecall(self, unpack(args))
		end
	)
	
	local LocalPlayer = game:GetService("Players").LocalPlayer
	
	function gettarget()
		local Character = LocalPlayer.Character or LocalPlayer.CharacterAdded:wait()
		local HumanoidRootPart = Character:WaitForChild("HumanoidRootPart")
		local maxdistance = math.huge
		local target
		for i, v in pairs(game:GetService("Workspace").Cashiers:GetChildren()) do
			if v:FindFirstChild("Head") and v:FindFirstChild("Humanoid") and v.Humanoid.Health > 0 then
				local distance = (HumanoidRootPart.Position - v.Head.Position).magnitude
				if distance < maxdistance then
					target = v
					maxdistance = distance
				end
			end
		end
		return target
	end
	
	for i, v in pairs(workspace:GetDescendants()) do
		if v:IsA("Seat") then
			v:Destroy()
		end
	end
	
	shared.MoneyFarm = texto -- Just execute shared.MoneyFarm = false to stop farming
	
	while shared.MoneyFarm do
		wait()
		local Target = gettarget()
		repeat
			wait()
			pcall(
				function()
					local Character = LocalPlayer.Character or LocalPlayer.CharacterAdded:wait()
					local HumanoidRootPart = Character:WaitForChild("HumanoidRootPart")
					local Combat = LocalPlayer.Backpack:FindFirstChild("Combat") or Character:FindFirstChild("Combat")
					if not Combat then
						Character:FindFirstChild("Humanoid").Health = 0
						return
					end
					HumanoidRootPart.CFrame = Target.Head.CFrame * CFrame.new(0, -2.5, 3)
					Combat.Parent = Character
					Combat:Activate()
				end
			)
		until not Target or Target.Humanoid.Health < 0
		for i, v in pairs(game:GetService("Workspace").Ignored.Drop:GetDescendants()) do
			if v:IsA("ClickDetector") and v.Parent and v.Parent.Name:find("Money") then
				local Character = LocalPlayer.Character or LocalPlayer.CharacterAdded:wait()
				local HumanoidRootPart = Character:WaitForChild("HumanoidRootPart")
				if (v.Parent.Position - HumanoidRootPart.Position).magnitude <= 18 then
					repeat
						wait()
						fireclickdetector(v)
					until not v or not v.Parent.Parent
				end
			end
		end
		wait(1)
	end
	end)

local Button6 = Section7:CreateButton("Best Animation", function()
	local Animate = game.Players.LocalPlayer.Character.Animate
	Animate.idle.Animation1.AnimationId = "http://www.roblox.com/asset/?id=782841498"
	Animate.idle.Animation2.AnimationId = "http://www.roblox.com/asset/?id=782845736"
	Animate.walk.WalkAnim.AnimationId = "http://www.roblox.com/asset/?id=616168032"
	Animate.run.RunAnim.AnimationId = "http://www.roblox.com/asset/?id=616163682"
	Animate.jump.JumpAnim.AnimationId = "http://www.roblox.com/asset/?id=1083218792"
	Animate.climb.ClimbAnim.AnimationId = "http://www.roblox.com/asset/?id=5319816685"
	Animate.fall.FallAnim.AnimationId = "http://www.roblox.com/asset/?id=707829716"
	game.Players.LocalPlayer.Character.Humanoid.Jump = true
end)

local Button6908 = Section7:CreateButton("Esp", function()

local Settings = {
    Box_Color = Color3.fromRGB(255, 0, 0),
    Tracer_Color = Color3.fromRGB(255, 0, 0),
    Tracer_Thickness = 1,
    Box_Thickness = 1,
    Tracer_Origin = "Bottom", -- Middle or Bottom if FollowMouse is on this won't matter...
    Tracer_FollowMouse = false,
    Tracers = false
}
local Team_Check = {
    TeamCheck = false, -- if TeamColor is on this won't matter...
    Green = Color3.fromRGB(0, 255, 0),
    Red = Color3.fromRGB(255, 0, 0)
}
local TeamColor = false

--// SEPARATION
local player = game:GetService("Players").LocalPlayer
local camera = game:GetService("Workspace").CurrentCamera
local mouse = player:GetMouse()

local function NewQuad(thickness, color)
    local quad = Drawing.new("Quad")
    quad.Visible = false
    quad.PointA = Vector2.new(0,0)
    quad.PointB = Vector2.new(0,0)
    quad.PointC = Vector2.new(0,0)
    quad.PointD = Vector2.new(0,0)
    quad.Color = color
    quad.Filled = false
    quad.Thickness = thickness
    quad.Transparency = 1
    return quad
end

local function NewLine(thickness, color)
    local line = Drawing.new("Line")
    line.Visible = false
    line.From = Vector2.new(0, 0)
    line.To = Vector2.new(0, 0)
    line.Color = color 
    line.Thickness = thickness
    line.Transparency = 1
    return line
end

local function Visibility(state, lib)
    for u, x in pairs(lib) do
        x.Visible = state
    end
end

local function ToColor3(col) --Function to convert, just cuz c;
    local r = col.r --Red value
    local g = col.g --Green value
    local b = col.b --Blue value
    return Color3.new(r,g,b); --Color3 datatype, made of the RGB inputs
end

local black = Color3.fromRGB(0, 0 ,0)
local function ESP(plr)
    local library = {
        --//Tracer and Black Tracer(black border)
        blacktracer = NewLine(Settings.Tracer_Thickness*2, black),
        tracer = NewLine(Settings.Tracer_Thickness, Settings.Tracer_Color),
        --//Box and Black Box(black border)
        black = NewQuad(Settings.Box_Thickness*2, black),
        box = NewQuad(Settings.Box_Thickness, Settings.Box_Color),
        --//Bar and Green Health Bar (part that moves up/down)
        healthbar = NewLine(3, black),
        greenhealth = NewLine(1.5, black)
    }

    local function Colorize(color)
        for u, x in pairs(library) do
            if x ~= library.healthbar and x ~= library.greenhealth and x ~= library.blacktracer and x ~= library.black then
                x.Color = color
            end
        end
    end

    local function Updater()
        local connection
        connection = game:GetService("RunService").RenderStepped:Connect(function()
            if plr.Character ~= nil and plr.Character:FindFirstChild("Humanoid") ~= nil and plr.Character:FindFirstChild("HumanoidRootPart") ~= nil and plr.Character.Humanoid.Health > 0 and plr.Character:FindFirstChild("Head") ~= nil then
                local HumPos, OnScreen = camera:WorldToViewportPoint(plr.Character.HumanoidRootPart.Position)
                if OnScreen then
                    local head = camera:WorldToViewportPoint(plr.Character.Head.Position)
                    local DistanceY = math.clamp((Vector2.new(head.X, head.Y) - Vector2.new(HumPos.X, HumPos.Y)).magnitude, 2, math.huge)
                    
                    local function Size(item)
                        item.PointA = Vector2.new(HumPos.X + DistanceY, HumPos.Y - DistanceY*2)
                        item.PointB = Vector2.new(HumPos.X - DistanceY, HumPos.Y - DistanceY*2)
                        item.PointC = Vector2.new(HumPos.X - DistanceY, HumPos.Y + DistanceY*2)
                        item.PointD = Vector2.new(HumPos.X + DistanceY, HumPos.Y + DistanceY*2)
                    end
                    Size(library.box)
                    Size(library.black)

                    --//Tracer 
                    if Settings.Tracers then
                        if Settings.Tracer_Origin == "Middle" then
                            library.tracer.From = camera.ViewportSize*0.5
                            library.blacktracer.From = camera.ViewportSize*0.5
                        elseif Settings.Tracer_Origin == "Bottom" then
                            library.tracer.From = Vector2.new(camera.ViewportSize.X*0.5, camera.ViewportSize.Y) 
                            library.blacktracer.From = Vector2.new(camera.ViewportSize.X*0.5, camera.ViewportSize.Y)
                        end
                        if Settings.Tracer_FollowMouse then
                            library.tracer.From = Vector2.new(mouse.X, mouse.Y+36)
                            library.blacktracer.From = Vector2.new(mouse.X, mouse.Y+36)
                        end
                        library.tracer.To = Vector2.new(HumPos.X, HumPos.Y + DistanceY*2)
                        library.blacktracer.To = Vector2.new(HumPos.X, HumPos.Y + DistanceY*2)
                    else 
                        library.tracer.From = Vector2.new(0, 0)
                        library.blacktracer.From = Vector2.new(0, 0)
                        library.tracer.To = Vector2.new(0, 0)
                        library.blacktracer.To = Vector2.new(0, 02)
                    end

                    --// Health Bar
                    local d = (Vector2.new(HumPos.X - DistanceY, HumPos.Y - DistanceY*2) - Vector2.new(HumPos.X - DistanceY, HumPos.Y + DistanceY*2)).magnitude 
                    local healthoffset = plr.Character.Humanoid.Health/plr.Character.Humanoid.MaxHealth * d

                    library.greenhealth.From = Vector2.new(HumPos.X - DistanceY - 4, HumPos.Y + DistanceY*2)
                    library.greenhealth.To = Vector2.new(HumPos.X - DistanceY - 4, HumPos.Y + DistanceY*2 - healthoffset)

                    library.healthbar.From = Vector2.new(HumPos.X - DistanceY - 4, HumPos.Y + DistanceY*2)
                    library.healthbar.To = Vector2.new(HumPos.X - DistanceY - 4, HumPos.Y - DistanceY*2)

                    local green = Color3.fromRGB(0, 255, 0)
                    local red = Color3.fromRGB(255, 0, 0)

                    library.greenhealth.Color = red:lerp(green, plr.Character.Humanoid.Health/plr.Character.Humanoid.MaxHealth);

                    if Team_Check.TeamCheck then
                        if plr.TeamColor == player.TeamColor then
                            Colorize(Team_Check.Green)
                        else 
                            Colorize(Team_Check.Red)
                        end
                    else 
                        library.tracer.Color = Settings.Tracer_Color
                        library.box.Color = Settings.Box_Color
                    end
                    if TeamColor == true then
                        Colorize(plr.TeamColor.Color)
                    end
                    Visibility(true, library)
                else 
                    Visibility(false, library)
                end
            else 
                Visibility(false, library)
                if game.Players:FindFirstChild(plr.Name) == nil then
                    connection:Disconnect()
                end
            end
        end)
    end
    coroutine.wrap(Updater)()
end

for i, v in pairs(game:GetService("Players"):GetPlayers()) do
    if v.Name ~= player.Name then
        coroutine.wrap(ESP)(v)
    end
end

game.Players.PlayerAdded:Connect(function(newplr)
    if newplr.Name ~= player.Name then
        coroutine.wrap(ESP)(newplr)
    end
end)
end)

-- Target Section 

local Section9 = Tab4:CreateSection("UI Toggle")

local Toggle31 = Section9:CreateToggle("", nil, function(State)
	Window:Toggle(State)
end)
Toggle31:CreateKeybind(tostring(Config.Keybind):gsub("Enum.KeyCode.", ""), function(Key)
	Config.Keybind = Enum.KeyCode[Key]
end)
Toggle31:SetState(true)

-- Finish <3

local aimbotEnabled = false
local smoothness = false
local aimbotTarg = nil
local aimbotPart = ""
