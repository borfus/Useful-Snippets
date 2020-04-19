nodes = {}

function countLinkedListNodes(nodeAddress)
    local counter = 0
	table.insert(nodes, nodeAddress)
    local next = readInteger(nodeAddress)
    while (next ~= nodeAddress) do
        counter = counter + 1
		table.insert(nodes, next)
        next = readInteger(next)
    end
    return counter
end

function findRootNode(nodeAddress)
    local size = countLinkedListNodes(nodeAddress)
    if (size ~= 0) then
        local next = readInteger(nodeAddress)
        for i,j in ipairs(nodes) do
			print(i, string.format("0x%x",j))
            next = readInteger(next)
        end
        return readInteger(next)
    end
end

local root = findRootNode(0x00AF0570)