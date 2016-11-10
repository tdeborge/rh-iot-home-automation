package com.redhat.riot.client;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttAsyncClient;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class WemosSensorSubscriber implements MqttCallback{

    String topic        = "Wemos/SmartHome/+/movement";
    String content      = "Message from MqttPublishSample";
    int qos             = 1;
    String broker       = "tcp://localhost:1883";
    String uname        = "admin";
    String pwd          = "admin";
    String clientId     = "Kura_Wemos_Listener";
    
    MqttAsyncClient wemosConnector;
    MqttConnectOptions connOpts;
    
    MemoryPersistence persistence = new MemoryPersistence();
    
    public static void main(String[] args){
        WemosSensorSubscriber wss = new WemosSensorSubscriber();
        try {
            wss.connectMqtt();
        } catch (MqttException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

    private void connectMqtt() throws MqttException {
        System.out.println("Initilizing the client");
        wemosConnector = new MqttAsyncClient(broker, clientId, persistence);
        connOpts = new MqttConnectOptions();
        connOpts.setCleanSession(true);
        connOpts.setUserName(uname);
        connOpts.setPassword(pwd.toCharArray());
        System.out.println("Connecting to broker: "+broker);
        IMqttToken tok = wemosConnector.connect(connOpts);
        tok.waitForCompletion(10000);
        wemosConnector.setCallback(this);
        wemosConnector.subscribe(topic, 1);
        System.out.println("Connection worked");
    }

    public void connectionLost(Throwable arg0) {
        // TODO Auto-generated method stub
        System.out.println("Connection is lost !!!!");
        try {
            wemosConnector.unsubscribe(topic);
            wemosConnector.disconnect();
        } catch (MqttException e) {
            // TODO Auto-generated catch block
           System.out.println("Fully disconnected!!!");
        }
        finally{
            wemosConnector = null;
        }
        boolean connected = false;
        while(!connected){
            try{
                connectMqtt();
                connected = true;
            }
            catch(MqttException e){
                try {
                    System.out.println("reconnect Connection Failed");
                    Thread.sleep(1000);
                } catch (InterruptedException e1) {
                    // TODO Auto-generated catch block
                    e1.printStackTrace();
                }
            }
        }
        
    }

    public void deliveryComplete(IMqttDeliveryToken arg0) {
        // TODO Auto-generated method stub
        System.out.println("The Delivery is Complete");
        
    }

    public void messageArrived(String topic, MqttMessage msg) throws Exception {
        System.out.println("message arrived on Topic: " + topic);
        System.out.println("The content is: " + msg);
    }
    

}
