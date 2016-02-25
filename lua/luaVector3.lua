------------------------------------------------------------------------------------------
-- lua 层的vector3
------------------------------------------------------------------------------------------
local vector3Meta 		= {}	-- vector3 元表(metatable)
local otherVector3Funs 	= {}	-- vector3 其他函数
------------------------------------------------------------------------------------------
-- vector3 + vector3
vector3Meta.__add = function(v1, v2)
	return vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z)
end
-- vector3 - vector3
vector3Meta.__sub = function(v1, v2)
	return vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z)
end
-- vector3 * number
vector3Meta.__mul = function(v1, f)
	if type(f) ~= "number" then return v1 end
	return vector3(v1.x * f, v1.y * f, v1.z * f)
end
-- vector3 / number
vector3Meta.__div = function(v1, f)
	if type(f) ~= "number" then return v1 end
	return vector3(v1.x / f, v1.y / f, v1.z / f)
end
-- .. print 方便调试
vector3Meta.__concat = function(t, v1)
	return t .. string.format("x = %f, y = %f, z = %f", v1.x, v1.y, v1.z)
end

-- 获取其他成员
vector3Meta.__index = otherVector3Funs

-- 禁止添加新的成员
vector3Meta.__newindex = function(t, k, v) assert(false, "vector3 not add new param <" .. k .. ">") end
------------------------------------------------------------------------------------------
-- 其他的函数
------------------------------------------------------------------------------------------
-- 标准化
function otherVector3Funs:normalize()
	local len = self:length()
	if len > 0 then
		self.x = self.x / len
		self.y = self.y / len
		self.z = self.z / len
    else
		self.x = 0
		self.y = 0
		self.z = 0
	end	
end

-- 长度
function otherVector3Funs:length()
	return math.sqrt(self.x^2 + self.y^2 + self.z^2) 
end

function otherVector3Funs:lengthSqr()
	return self.x^2 + self.y^2 + self.z^2
end

function otherVector3Funs:toStr()
	return string.format("x = %f, y = %f, z = %f", self.x, self.y, self.z)
end

function otherVector3Funs:printf()
	print(self:toStr())
end

-- 这部分函数是为了修改本身添加，考虑到不需要创建新的数据结构处理，元表处理都会有新的结构生成
function otherVector3Funs:add(v3)
	self.x = self.x + v3.x
	self.y = self.y + v3.y
	self.z = self.z + v3.z
end

function otherVector3Funs:sub(v3)
	self.x = self.x - v3.x
	self.y = self.y - v3.y
	self.z = self.z - v3.z
end

function otherVector3Funs:mul(f)
	self.x = self.x * f
	self.y = self.y * f
	self.z = self.z * f
end

function otherVector3Funs:div(f)
	self.x = self.x / f
	self.y = self.y / f
	self.z = self.z / f
end

function otherVector3Funs:copy()
	return vector3(self.x, self.y, self.z)
end
------------------------------------------------------------------------------------------
-- 生成一个vector3
------------------------------------------------------------------------------------------
function vector3(x, y, z)
	local v3 = {x = x, y = y, z = z}
	setmetatable(v3, vector3Meta)
	return v3
end
