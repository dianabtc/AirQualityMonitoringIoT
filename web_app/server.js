const AWS = require('aws-sdk');
const express = require('express');
const app = express();
const PORT = 3000;
const cors = require('cors');
app.use(cors());

AWS.config.update({ region: 'eu-central-1' });
const dynamoDB = new AWS.DynamoDB.DocumentClient();

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

app.listen(PORT, () => {
    console.log(`Running on http://localhost:${PORT}`);
});