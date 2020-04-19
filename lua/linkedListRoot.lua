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
			scanMemoryForPointerAndSize(j, size)
            next = readInteger(next)
        end
        return readInteger(next)
    end
end

function scanMemoryForPointerAndSize(address, size)
    me = createMemScan(MainForm.ProgressBar)
	me.firstScan(soExactValue, vtDword, rtRounded, address, nil, 0, 0xffffffffffffffff, '+W-X-C', fsmAligned, '4', false, true, false, false)
	me.waitTillDone()

	local fl = createFoundList(me)
	fl.initialize()

	local count = me.FoundList.Count
	if count > 0 then
		for i=0, count-1 do
			local sizeCandidate = readInteger(tonumber(fl[i], 16) + 4)
			if (sizeCandidate == size) then
			    print('List location: 0x' .. fl[i])
				print(string.format('Base node: 0x%x', address))
            end
		end
	end
end

findRootNode(anyNodeAddress)