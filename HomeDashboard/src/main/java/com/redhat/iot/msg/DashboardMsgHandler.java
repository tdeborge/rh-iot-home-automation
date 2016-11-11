package com.redhat.iot.msg;

import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttAsyncClient;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redhat.iot.gui.HomeDashboard;

public class DashboardMsgHandler implements MqttCallback, IMqttActionListener {

    private static final Logger s_logger = LoggerFactory.getLogger(HomeDashboard.class);
    private HomeDashboard hdb;
    
    private long m_moveTick = 0;
    private long m_lightTime = 0;
    private long m_lightTick = 0;
    private boolean m_lightOn = false;

    private String m_topics;
    private String[] m_topicList;
    private int[] m_qosList;
    private int m_qos = 0;
    private String m_brokerURL;
    private String m_uname;
    private String m_pwd;
    private String m_clientId;

    private MqttAsyncClient m_wemosConnector;
    private  MqttConnectOptions connOpts;
    private MemoryPersistence m_persistence = new MemoryPersistence();
    
    private long m_timeOn = System.currentTimeMillis();;

    public DashboardMsgHandler(HomeDashboard hd) {
        this.hdb = hd;
        this.m_topics = HomeDashboard.getString("dashboard.msg.topics").trim();
        this.m_topicList = m_topics.split(";");
        this.m_qos = Integer.parseInt(HomeDashboard.getString("dashboard.msg.qos").trim());
        m_qosList = new int[m_topicList.length];
        for(int i = 0; i < m_topicList.length; i++){
            m_qosList[i] = m_qos;
        }
        this.m_brokerURL = HomeDashboard.getString("dashboard.msg.BrokerURL").trim();
        this.m_uname = HomeDashboard.getString("dashboard.msg.UserName").trim();
        this.m_pwd = HomeDashboard.getString("dashboard.msg.Password").trim();
        this.m_clientId = HomeDashboard.getString("dashboard.msg.clientID").trim();

        printVariables();
    }

    private void printVariables() {
        s_logger.info("---------------------------------------");
        s_logger.info("Broker URL: " + m_brokerURL);
        s_logger.info("Username: " + m_uname);
        s_logger.info("Password: " + m_pwd);
        s_logger.info("ClientID: " + m_clientId);
        for (int i = 0; i < m_topicList.length; i++) {
            s_logger.info("Topic: " + m_topicList[i]);
        }
    }

    public void createMQTTConnection() {
        connOpts = new MqttConnectOptions();
        connOpts.setCleanSession(true);
        connOpts.setUserName(m_uname);
        connOpts.setPassword(m_pwd.toCharArray());
        s_logger.info("Connecting to broker: " + m_brokerURL);
        try {
            m_wemosConnector = new MqttAsyncClient(m_brokerURL, m_clientId, m_persistence);
            m_wemosConnector.connect(connOpts, null, this);

        } catch (MqttException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            System.exit(0);
        }
//        s_logger.info("tok status: " + tok.isComplete());
        m_wemosConnector.setCallback(this);
    }

    @Override
    public void onFailure(IMqttToken tok, Throwable ex) {
        s_logger.error("ON-FAILURE: Not Connected ... " + ex.getMessage());
        hdb.setConnectFailed();
        disconnectMQTT();
        try {
            s_logger.error("Connection failed ... wait 5 seconds before re-try");
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }       
        createMQTTConnection();
    }

    @Override
    public void onSuccess(IMqttToken tok) {
        s_logger.info("Connection Succeeded on " + tok.getClient().getServerURI());
        
        try {
            m_wemosConnector.subscribe(m_topicList, m_qosList);
        } catch (MqttException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        hdb.setConnectSuccess();
        hdb.setTickerValues(m_moveTick,m_lightTime,m_lightTick,m_lightOn);
    }

    @Override
    public void connectionLost(Throwable t) {
        hdb.setConnectFailed();
        s_logger.error("CONNECTIO LOST Not Connected ... " + t.getMessage());
        s_logger.error("Connection Dropped ... initiating re-connect");
        disconnectMQTT();
        try {
            s_logger.error("Connection failed ... wait 5 seconds before re-try");
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }       
        createMQTTConnection();
    }

    @Override
    public void deliveryComplete(IMqttDeliveryToken arg0) {
        // TODO Auto-generated method stub

    }

    @Override
    public void messageArrived(String topic, MqttMessage msg) throws Exception {
        s_logger.info("Message arrived on topic " + topic + " and value " + msg);
        if(topic.endsWith("/light")){
            this.m_lightTick++;
            if(new String(msg.getPayload()).equals("0")){
                m_lightOn = false;
                long current = System.currentTimeMillis();
                long delta = (current - m_timeOn) / 1000;
                m_lightTime += delta;
            }
            else{
                m_lightOn = true;
                m_timeOn = System.currentTimeMillis();
            }
            //calculate the time here between an on an an off message
        }
        if(topic.endsWith("/movement")){
            this.m_moveTick++;
            //calculate the time here between an on an an off message
        }
        hdb.setTickerValues(m_moveTick,m_lightTime,m_lightTick,m_lightOn);
    }
    
    private void disconnectMQTT(){
        try {
            m_wemosConnector.unsubscribe(m_topics);
            m_wemosConnector.disconnect();
        } catch (MqttException e2) {
            // TODO Auto-generated catch block
            s_logger.info("Fully disconnected!!!");
        } finally {
            m_wemosConnector = null;
            connOpts = null;
        }
    }
}
