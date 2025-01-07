const AWS = require('aws-sdk');
const express = require('express');
const app = express();
const PORT = 3000;
const cors = require('cors');
const sns = new AWS.SNS({ region: 'eu-central-1' });
app.use(cors());
app.use(express.json());

AWS.config.update({ region: 'eu-central-1' });
const dynamoDB = new AWS.DynamoDB.DocumentClient();
const iotData = new AWS.IotData({ endpoint: 'a2o3p0uz5lezih-ats.iot.eu-central-1.amazonaws.com' });

app.get('/temperature', async (req, res) => {
    const params = {
        TableName: 'SensorData',
        KeyConditionExpression: 'sensorType = :sensorType',
        ExpressionAttributeValues: {
            ':sensorType': 'temperature'
        },
        Limit: 10,
        ScanIndexForward: false
    };

    try {
        const data = await dynamoDB.query(params).promise();
        res.json(data.Items.reverse());
    } catch (error) {
        console.error(error);
        res.status(500).send('Error reading temperature data.');
    }
});

app.get('/humidity', async (req, res) => {
    const params = {
        TableName: 'SensorData',
        KeyConditionExpression: 'sensorType = :sensorType',
        ExpressionAttributeValues: {
            ':sensorType': 'humidity'
        },
        Limit: 10,
        ScanIndexForward: false
    };

    try {
        const data = await dynamoDB.query(params).promise();
        res.json(data.Items.reverse());
    } catch (error) {
        console.error(error);
        res.status(500).send('Error reading humidity data.');
    }
});

app.get('/gas', async (req, res) => {
    const params = {
        TableName: 'SensorData',
        KeyConditionExpression: 'sensorType = :sensorType',
        ExpressionAttributeValues: {
            ':sensorType': 'gas'
        },
        Limit: 10,
        ScanIndexForward: false
    };

    try {
        const data = await dynamoDB.query(params).promise();
        res.json(data.Items.reverse());
    } catch (error) {
        console.error(error);
        res.status(500).send('Error reading gas data.');
    }
});

app.post('/send-command', async (req, res) => {
    // {"command": "on/off"}
    const { command } = req.body;

    const params = {
        topic: 'commands/fan',
        payload: JSON.stringify({ command: command }),
        qos: 0,
    };

    try {
        await iotData.publish(params).promise();
        res.send('Command sent!');
    } catch (error) {
        console.error(error);
        res.status(500).send('Failed to send command.');
    }
});

app.listen(PORT, () => {
    console.log(`Running on http://localhost:${PORT}`);
});

setInterval(async () => {
    const params = {
        TableName: 'SensorData',
        KeyConditionExpression: 'sensorType = :sensorType',
        ExpressionAttributeValues: {
            ':sensorType': 'gas'
        },
        Limit: 10,
        ScanIndexForward: false
    };

    try {
        const data = await dynamoDB.query(params).promise();
        const latestData = data.Items.reverse()[9];
        console.log('Latest data: ', latestData);

        if (latestData && latestData.value > 1500) {
            const notificationParams = {
                Message: `Gas concentration is too high! Value: ${latestData.value}`,
                TopicArn: 'arn:aws:sns:eu-central-1:463470938276:AirQualityAlerts',
            };

            try {
                const snsResponse = await sns.publish(notificationParams).promise();
                console.log(`Notification sent. Message ID: ${snsResponse.MessageId}`);
            } catch (snsError) {
                console.error(`Failed to send notification: ${snsError.message}`);
            }
        }
    } catch (error) {
        console.error('Error in periodic alert check:', error);
    }
}, 10000);



