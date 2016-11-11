package com.redhat.riot.client;

import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttAsyncClient;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class WemosAsyncSensorSubscriber implements MqttCallbackExtended, IMqttActionListener {

    String topic = "Wemos/Home/#";
    String content = "Message from MqttPublishSample";
    int qos = 1;
    String broker = "tcp://localhost:1883";
    String uname = "admin";
    String pwd = "admin";
    String clientId = "Eclipse_Wemos_Listener";

    MqttAsyncClient wemosConnector;
    MqttConnectOptions connOpts;

    MemoryPersistence persistence = new MemoryPersistence();

    public static void main(String[] args) {
        WemosAsyncSensorSubscriber wss = new WemosAsyncSensorSubscriber();
        wss.connectMqtt();
    }

    private void connectMqtt() {
        System.out.println("Initilizing the client");
        connOpts = new MqttConnectOptions();
        connOpts.setCleanSession(true);
        connOpts.setUserName(uname);
        connOpts.setPassword(pwd.toCharArray());
        System.out.println("Connecting to broker: " + broker);
        IMqttToken tok = null;
        try {
            wemosConnector = new MqttAsyncClient(broker, clientId, persistence);
            tok = wemosConnector.connect(connOpts,broker,this);
        } catch (MqttException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            System.exit(0);
        }
        wemosConnector.setCallback(this);
        //tok.setActionCallback(this);
        
//        tok.setActionCallback(new IMqttActionListener() {
//            @Override
//            public void onSuccess(IMqttToken arg0) {
//                 try {
//                    wemosConnector.subscribe(topic, 2, null, new IMqttActionListener() {
//                          @Override
//                          public void onSuccess(IMqttToken asyncActionToken) {
//                              System.out.println("Successfully subscribed to topic.");
//                          }
//
//                          @Override
//                          public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
//                              System.out.println("Failed to subscribed to topic.");
//                          }
//                      });
//                } catch (MqttException e) {
//                    // TODO Auto-generated catch block
//                    e.printStackTrace();
//                }
//            }
//
//            @Override
//            public void onFailure(IMqttToken arg0, Throwable arg1) {
//                System.out.println("error on the connection level");
//            }
//          });
        System.out.println(""+ tok.isComplete());
//        tok.waitForCompletion();
        // tok.waitForCompletion(10000);
//        wemosConnector.setCallback(this);
//        wemosConnector.subscribe(topic, 1);

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
        } finally {
            wemosConnector = null;
            connOpts = null;
        }
        
        connectMqtt();
        
//        boolean connected = false;
//        while (!connected) {
//            try {
//                connectMqtt();
//                connected = true;
//            } catch (MqttException e) {
//                try {
//                    System.out.println("reconnect Connection Failed");
//                    Thread.sleep(1000);
//                } catch (InterruptedException e1) {
//                    // TODO Auto-generated catch block
//                    e1.printStackTrace();
//                }
//            }
//        }

    }

    public void deliveryComplete(IMqttDeliveryToken arg0) {
        // TODO Auto-generated method stub
        System.out.println("The Delivery is Complete");

    }

    public void messageArrived(String topic, MqttMessage msg) throws Exception {
        System.out.println("message arrived on Topic: " + topic);
        System.out.println("The content is: " + msg);
    }

    @Override
    public void connectComplete(boolean reconnect, String uri) {
        System.out.println("The connection is made to " + uri);
        System.out.println("is this a reconnect? " + reconnect);
    }

    @Override
    public void onFailure(IMqttToken tok, Throwable e) {
        System.out.println("Error on this token " + tok.getTopics());
        System.out.println("Error is " + e.getMessage());
        System.out.println("Sleeping timeout for the reconnect");
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
        try {
            wemosConnector.unsubscribe(topic);
            wemosConnector.disconnect();
        } catch (MqttException e2) {
            // TODO Auto-generated catch block
            System.out.println("Fully disconnected!!!");
        } finally {
            wemosConnector = null;
            connOpts = null;
        }
        
        connectMqtt();
    }

    @Override
    public void onSuccess(IMqttToken tok) {
        System.out.println("Connection Succeeded on " + tok.getClient().getServerURI());
       
        try {
            wemosConnector.subscribe(topic, 1);
        } catch (MqttException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

}
