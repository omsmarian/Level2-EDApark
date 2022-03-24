/*
 * Simple MQTT Client
 *
 * Copyright (C) 2022 Marc S. Ressl
 *
 * libmosquitto documentation:
 * https://mosquitto.org/api/files/mosquitto-h.html
 */

#include <cstring>
#include <iostream>

static void onMQTTMessage(struct mosquitto *mosquittoClient,
                          void *context,
                          const struct mosquitto_message *message);

#include "MQTTClient.h"

using namespace std;

// Awful but necessary global variable:
static bool isMosquittoInitialized = false;

// MQTT message callback.
static void onMQTTMessage(struct mosquitto *mosquittoClient,
                          void *context,
                          const struct mosquitto_message *message)
{
    MQTTClient *mqttClient = (MQTTClient *)context;

    MQTTMessage mqttMessage;
    mqttMessage.topic = message->topic;
    mqttMessage.payload.resize(message->payloadlen);
    memcpy(mqttMessage.payload.data(), message->payload, message->payloadlen);

    mqttClient->lastMessages.push_back(mqttMessage);
}

/*
 * MQTTClient::connect
 *
 * Constructs an MQTT client object.
 *
 * Parameters:
 *  clientId -   MQTT client identifier
 */
MQTTClient::MQTTClient(string clientId)
{
    if (!isMosquittoInitialized)
    {
        mosquitto_lib_init();

        isMosquittoInitialized = true;
    }

    const bool cleanSession = true;

    mosquittoInstance = mosquitto_new(clientId.c_str(), cleanSession, this);

    mosquitto_message_callback_set(mosquittoInstance, onMQTTMessage);

    connected = false;
}

MQTTClient::~MQTTClient()
{
    mosquitto_destroy(mosquittoInstance);
}

/*
 * MQTTClient::connect
 *
 * Connects to an MQTT server without encryption.
 *
 * Parameters:
 *  host -       Host to connect to (IP address or domain name)
 *  username -   MQTT username
 *  password -   MQTT password
 */
bool MQTTClient::connect(string host, int port, string username, string password)
{
    int errorCode;

    mosquitto_username_pw_set(mosquittoInstance,
                              username.c_str(),
                              password.c_str());

    const int keepalive = 60;

    errorCode = mosquitto_connect(mosquittoInstance,
                                  host.c_str(),
                                  port,
                                  keepalive);

    if (errorCode == MOSQ_ERR_SUCCESS)
        connected = true;

    return connected;
}

/*
 * MQTTClient::isConnected
 *
 * Tells whether the connection is up.
 */
bool MQTTClient::isConnected()
{
    return connected;
}

/*
 * MQTTClient::disconnect
 *
 * Disconnects from the MQTT server.
 */
void MQTTClient::disconnect()
{
    mosquitto_disconnect(mosquittoInstance);

    connected = false;
}

/*
 * MQTTClient::publish
 *
 * Publishes an MQTT message to the server.
 * 
 * Parameters:
 *  topic -     The MQTT topic
 *  payload -   The data to be sent
 * 
 * Returns: call succeeded
 */
bool MQTTClient::publish(string topic, vector<char> &payload)
{
    const int qos = 0;
    const bool retain = false;

    int errorCode = mosquitto_publish(mosquittoInstance,
                                      NULL,
                                      topic.c_str(),
                                      (int)payload.size(),
                                      payload.data(),
                                      qos,
                                      retain);

    if (errorCode == MOSQ_ERR_NO_CONN)
        connected = false;

    return (errorCode == MOSQ_ERR_SUCCESS);
}

/*
 * MQTTClient::subscribe
 *
 * Sends an MQTT subscription request.
 * Topic may be straight or contain wildcards ('+' for any topic, '#' for anything below in tree).
 * 
 * Parameters:
 *  topic -     The MQTT topic
 * 
 * Returns: call succeeded
 */
bool MQTTClient::subscribe(string topic)
{
    const int qos = 0;

    int errorCode = mosquitto_subscribe(mosquittoInstance,
                                        NULL,
                                        topic.c_str(),
                                        qos);

    if (errorCode == MOSQ_ERR_NO_CONN)
        connected = false;

    return (errorCode == MOSQ_ERR_SUCCESS);
}

/*
 * MQTTClient::unsubscribe
 *
 * Sends an MQTT unsubscription request. Should match a previous subscription request.
 * 
 * Parameters:
 *  topic -     The MQTT topic
 * 
 * Returns: call succeeded
 */
bool MQTTClient::unsubscribe(string topic)
{
    int errorCode = mosquitto_unsubscribe(mosquittoInstance,
                                          NULL,
                                          topic.c_str());

    if (errorCode == MOSQ_ERR_NO_CONN)
        connected = false;

    return (errorCode == MOSQ_ERR_SUCCESS);
}

/*
 * MQTTClient::getMessages
 *
 * Retrieve latest messages. Should be called quite frequently so messages do not accumulate.
 * 
 * Returns: the MQTT messages
 */
vector<MQTTMessage> MQTTClient::getMessages()
{
    vector<MQTTMessage> messages;

    while (true)
    {
        const int timeout = 0;
        const int maxPackets = 1;

        int errorCode = mosquitto_loop(mosquittoInstance, timeout, maxPackets);

        if ((errorCode == MOSQ_ERR_NO_CONN) ||
            (errorCode == MOSQ_ERR_CONN_LOST))
            connected = false;

        if (!lastMessages.size())
            break;

        // Moves lastMessages to messages
        messages.insert(messages.end(), lastMessages.begin(), lastMessages.end());
        lastMessages.clear();
    }

    return messages;
}
