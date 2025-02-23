function Decoder(topic, payload) 
{
    // Transform incoming payload to JSON
    payload = JSON.parse(payload);
    payloadData = payload.payload;
    
    // Remember, data is: {"channel":0,"from":4201002620,"id":1242862792,"payload":{"air_util_tx":3.37072229385376,"battery_level":91,"channel_utilization":5.82999992370605,"voltage":4.06899976730347},"sender":"!fa66367c","timestamp":1710076900,"to":4294967295,"type":"telemetry"}
    
    // Extract from payload, do calculation
    var from = payload.from;
    var type = payload.type;
    var timestamp = payload.timestamp;
    var hops_away = payload.hops_away;
    var node;
    
    if      (from == 4201002620) {node = "Heltec LoRa32 V3";}
    else if (from == 2053978516) {node = "Lilygo T-Beam";}
    else if (from == 808617300)  {node = "Heltec LoRa32 V3 H01";}
    else if (from == 3662934188) {node = "Heltec LoRa32 V3 H02";}
    else if (from == 2692927950) {node = "RAK4631 RAK1";}
    else if (from == 3118357274) {node = "RAK4631 RAK2";}
    else                         {node = "unknown";}
    
    if (from != 2692927950)
    {
        // Forward Data to Datacake Device API using Serial, Field-Identifier
        return [
            {
                device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                field: "from",
                value: from
            },
            {
                device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                field: "node",
                value: node
            },
            {
                device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                field: "type",
                value: type
            },
            {
                device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                field: "timestamp",
                value: timestamp
            },
            {
                device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                field: "hops_away",
                value: hops_away
            }
        ];
    }
    else
    {
        if (type == "telemetry")
        {
            var air_util_tx = payloadData.air_util_tx;
            var hops_away = payload.hops_away;
        
            if (air_util_tx >= 0)
            {
                // Forward Data to Datacake Device API using Serial, Field-Identifier
                return [
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "from",
                        value: from
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "node",
                        value: node
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "type",
                        value: type
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "timestamp",
                        value: timestamp
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "air_util_tx",
                        value: air_util_tx
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "hops_away",
                        value: hops_away
                    } 
                ]; 
            }
            else
            {
                var SHTC3_rh = payloadData.relative_humidity;
                var SHTC3_temp = payloadData.temperature;
                var voltage = payloadData.voltage;
                var current = payloadData.current * (-1);
                var hops_away = payload.hops_away;
                var air_util_tx = payloadData.air_util_tx;
                
                // Forward Data to Datacake Device API using Serial, Field-Identifier
                return [
                   {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "from",
                        value: from
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "node",
                        value: node
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "type",
                        value: type
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "timestamp",
                        value: timestamp
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "humidity",
                        value: SHTC3_rh
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "temperature",
                        value: SHTC3_temp
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "voltage",
                        value: voltage
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "current",
                        value: current
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "air_util_tx",
                        value: air_util_tx
                    },
                    {
                        device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                        field: "hops_away",
                        value: hops_away
                    } 
                ];
            }   
        }
        else if (type == "position")
        {
            var altitude = payloadData.altitude;
            var latitude = payloadData.latitude_i/1e7;
            var longitude = payloadData.longitude_i/1e7;
            var loc = "(" + latitude + "," + longitude + ")"
            var hops_away = payload.hops_away;
        
            // Forward Data to Datacake Device API using Serial, Field-Identifier
            return [
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "from",
                    value: from
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "node",
                    value: node
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "type",
                    value: type
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "timestamp",
                    value: timestamp
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "altitude",
                    value: altitude
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "location",
                    value: loc
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "hops_away",
                    value: hops_away
                } 
            ];
        }
        else if (type == "text")
        {
            var text = payloadData.text;
            var DS18B20_temperature = parseFloat(text.slice(16));
            var hops_away = payload.hops_away;
            
            // Forward Data to Datacake Device API using Serial, Field-Identifier
            return [
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "from",
                    value: from
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "node",
                    value: node
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "type",
                    value: type
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "timestamp",
                    value: timestamp
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "DS18B20_temperature",
                    value: DS18B20_temperature
                },
                {
                    device: "e9055050-af37-4836-a50a-6d90968f7500", // Serial Number or Device ID
                    field: "hops_away",
                    value: hops_away
                }          
            ];
        }
    }
}