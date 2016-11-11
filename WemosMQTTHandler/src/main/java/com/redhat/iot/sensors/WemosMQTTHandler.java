package com.redhat.iot.sensors;

import java.util.ArrayList;
import java.util.Date;
import java.util.Map;

import org.eclipse.kura.KuraException;
import org.eclipse.kura.cloud.CloudClient;
import org.eclipse.kura.cloud.CloudClientListener;
import org.eclipse.kura.cloud.CloudService;
import org.eclipse.kura.configuration.ConfigurableComponent;
import org.eclipse.kura.crypto.CryptoService;
import org.eclipse.kura.message.KuraPayload;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttAsyncClient;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import org.osgi.service.component.ComponentContext;
import org.osgi.service.component.ComponentException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class WemosMQTTHandler implements ConfigurableComponent, CloudClientListener, MqttCallback, IMqttActionListener {

    private static final Logger s_logger = LoggerFactory.getLogger(WemosMQTTHandler.class);

    private final String APP_ID = "WEMOS-Sensors";
    private final String SMARTLIGHT = "light";
    private final String CLOUDPUBLISH = "SmartCloudPublish";


    private CloudService m_cloudService;
    private CryptoService m_cryptoService;
    private static CloudClient m_cloudClient;

    // Messaging Definitions
    private String m_subTopic = "";
    private String m_pubTopic = "";
    private int m_qos = 1;
    private boolean m_cleansession;
    private String m_broker = "tcp://localhost:1883";
    private String m_uname = "admin";
    private char[] m_pwd;
    private String m_password;
    private String m_clientId = "Kura_Wemos_Listener";
    private long m_connectionInterval = 5000;

    // Capabilities
    ArrayList<String> m_capabilities;
    private boolean m_smartLight = false;
    private boolean m_cloudIntegrations;
    private boolean m_subEnabled = false;

    // Messaging
    private MqttAsyncClient m_wemosConnector;
    private MqttConnectOptions m_connOpts;
    private MemoryPersistence m_persistence = new MemoryPersistence();


    // --------------------------------------------------------------------
    //
    // Kura provided Services 
    //  CloudService for Cloud Communications
    //
    //
    // --------------------------------------------------------------------
    public void setCloudService(CloudService cloudService) {
        m_cloudService = cloudService;
    }

    public void unsetCloudService(CloudService cloudService) {
        m_cloudService = null;
    }

    public void setCryptoService(CryptoService crypt) {
        m_cryptoService = crypt;
    }

    public void unsetCryptoService(CryptoService crypt) {
        m_cryptoService = null;
    }

    // --------------------------------------------------------------------
    //
    // Activation APIs
    //
    // --------------------------------------------------------------------
    protected void activate(ComponentContext context, Map<String, Object> properties) {
        s_logger.info("Activating WEMOS implementation ...");
        updateProperties(properties);
        printVariables();
        try {
            m_cloudClient = m_cloudService.newCloudClient(APP_ID);
            m_cloudClient.addCloudClientListener(this);
        } catch (KuraException e1) {
            s_logger.error("Error starting component", e1);
            throw new ComponentException(e1);
        }
        if (m_subEnabled) {
            createMQTTConnection();
        }
    }
    
    protected void deactivate(ComponentContext context) {
        s_logger.info("Deactivating WEMOS implementation...");
        if (m_subEnabled) {
            stopMQTTConnection();
        }
    }
    
    protected void updated(Map<String, Object> properties) {
        s_logger.info("Updating the WEMOS implementation ...");
        if (m_subEnabled) {
            stopMQTTConnection();
        }
        updateProperties(properties);
        printVariables();
        if (m_subEnabled) {
            createMQTTConnection();
        }
    }
    
    // --------------------------------------------------------------------
    //
    // MQTT Handling
    //
    // --------------------------------------------------------------------

    private void createMQTTConnection() {
        s_logger.info("Initilizing the client");
        this.m_connOpts = new MqttConnectOptions();
        this.m_connOpts.setCleanSession(m_cleansession);
        this.m_connOpts.setUserName(m_uname);
        this.m_connOpts.setPassword(m_password.toCharArray());
        this.m_connOpts.setConnectionTimeout(30);
        // this.m_broker = "tcp://mbpTimDeBorger.local:1883";
        s_logger.info("Connecting to broker: " + m_broker);
        IMqttToken tok;

        // boolean connected = false;
        try {
            this.m_wemosConnector = new MqttAsyncClient(this.m_broker, this.m_clientId, this.m_persistence);
            tok = m_wemosConnector.connect(m_connOpts, null, this);
            m_wemosConnector.setCallback(this);
        } catch (MqttException e) {
            s_logger.error("This exception should not happen if the URL is correct!!!!");
            throw new ComponentException("Connection to the Broker failed: " + m_broker + " ... " + e.getMessage());
        }
        s_logger.debug("Completed or not we will continue ... completed? :" + tok.isComplete());
    }

    private void stopMQTTConnection() {
        s_logger.info("Stopping the connection");
        try {
            m_wemosConnector.unsubscribe(m_subTopic);
            m_wemosConnector.disconnect();
        } catch (MqttException e) {
            // TODO Auto-generated catch block
            System.out.println("Fully disconnected!!!");
        } finally {
            m_wemosConnector = null;
            m_connOpts = null;
        }
    }

    // --------------------------------------------------------------------
    //
    // MQTT CallBack Handling
    //
    // --------------------------------------------------------------------
    
    @Override
    public void connectionLost(Throwable arg0) {
        s_logger.info("Lost MQTT WEMOS implementation Connection...");
        stopMQTTConnection();
        if (m_subEnabled) {
            createMQTTConnection();
        }
    }

    @Override
    public void deliveryComplete(IMqttDeliveryToken arg0) {
        s_logger.info("The Delivery is Complete");
    }

    @Override
    public void onFailure(IMqttToken tok, Throwable ex) {
        s_logger.error("Connection Failed ... Sleeping and retrying: " + ex.getMessage());
        m_wemosConnector = null;
        m_connOpts = null;
        try {
            s_logger.info("Sleeping before reconnect");
            Thread.sleep(m_connectionInterval);
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        s_logger.info("Trying to reconnect");
        createMQTTConnection();
    }

    @Override
    public void onSuccess(IMqttToken token) {
        s_logger.info("Connected to Broker " + m_broker + token.isComplete());
        try {
            m_wemosConnector.subscribe(m_subTopic + "/#", m_qos);
            s_logger.info("Subscription Complete");
        } catch (MqttException e) {
            // TODO Auto-generated catch block
            s_logger.error("Subscription Failed");
        }
    }

    // --------------------------------------------------------------------
    //
    // Helper section
    //
    // --------------------------------------------------------------------

    private void updateProperties(Map<String, Object> properties) {
        if (properties != null) {
            this.m_capabilities = new ArrayList<String>();
            this.m_subEnabled = (boolean) properties.get("subEnabled");
            this.m_subTopic = (String) properties.get("SubscribingTopic");
            this.m_pubTopic = (String) properties.get("PublishingTopic");
            this.m_clientId = (String) properties.get("clientId");
            this.m_broker = (String) properties.get("BrokerURL");
            this.m_uname = (String) properties.get("UserName");
            this.m_pwd = ((String) properties.get("Password")).toCharArray();
            try {
                this.m_password = new String(m_cryptoService.decryptAes(m_pwd));
            } catch (KuraException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            this.m_qos = ((Integer) properties.get("QOS")).intValue();
            this.m_cleansession = (boolean) properties.get("cleansession");
            this.m_connectionInterval = ((Integer) properties.get("connectionInterval")).intValue();
            this.m_cloudIntegrations = (boolean) properties.get("CloudIntegrations");
            if(m_cloudIntegrations){
                if(!m_capabilities.contains(CLOUDPUBLISH)){
                    m_capabilities.add(CLOUDPUBLISH);
                }
            }
            this.m_smartLight = (boolean) properties.get("smartlight");
            if (m_smartLight) {
                if (!m_capabilities.contains(SMARTLIGHT)) {
                    m_capabilities.add(SMARTLIGHT);
                }
            }

            // if there are no sensors enabled ... move configuration to disableds
            if (m_capabilities.size() < 1) {
                s_logger.info("No Sensors enabled ... Disabling the subscriber");
                this.m_subEnabled = false;
            }
        }
    }

    private void printVariables() {
        s_logger.info("Enabled Subscription? " + this.m_subEnabled);
        s_logger.info("Broker URL: " + this.m_broker);
        s_logger.info("Username: " + this.m_uname);
        s_logger.info("encrypted PWD: " + this.m_pwd.toString());
        s_logger.info("Password: " + this.m_password);
        s_logger.info("Client-ID: " + this.m_clientId);
        s_logger.info("QOS: " + m_qos);
        s_logger.info("Connection interval: " + this.m_connectionInterval);
        s_logger.info("Subscription prefix: " + this.m_subTopic);
        s_logger.info("Publish Prefix: " + this.m_pubTopic);
        s_logger.info("SmartLight Enabled: " + this.m_smartLight);
        s_logger.info("Send smart messages to cloud? " + m_cloudIntegrations);
    }

    // --------------------------------------------------------------------
    //
    // CloudClientListener APIs
    //
    // --------------------------------------------------------------------
    @Override
    public void onConnectionEstablished() {
        s_logger.debug("Cloud Client Connection Established");
    }

    @Override
    public void onConnectionLost() {
        s_logger.debug("Cloud Client Connection Lost");
    }

    @Override
    public void onControlMessageArrived(String arg0, String arg1, KuraPayload arg2, int arg3, boolean arg4) {
        s_logger.debug("Cloud Client Control Message Arrived");
    }

    @Override
    public void onMessageArrived(String arg0, String arg1, KuraPayload arg2, int arg3, boolean arg4) {
        s_logger.debug("Cloud Client  Message Arrived");
    }

    @Override
    public void onMessageConfirmed(int arg0, String arg1) {
        s_logger.debug("Cloud Client  Message Confirmed");
    }

    @Override
    public void onMessagePublished(int arg0, String arg1) {
        s_logger.debug("Cloud Client  Message Published");
    }

    // --------------------------------------------------------------------
    //
    // Sending information to the Cloud APIs
    //
    // --------------------------------------------------------------------
 
    @Override
    public void messageArrived(String topic, MqttMessage msg) throws Exception {
        s_logger.debug("message arrived on Topic: " + topic);
        //Determine the asset and the ID
        String value = new String(msg.getPayload());
        s_logger.debug("The content is: " + msg + "/" + value);
        
        String id = "";
        String asset = "";
   
        String[] tokens = topic.split("/");
        if(tokens.length > 1){
            asset = tokens[tokens.length -1];
            id = tokens[tokens.length -2];
        }
        s_logger.debug("The Asset name is: " + asset);
        s_logger.debug("The ComponentID is: " + id);
        
        if(m_capabilities.contains(this.CLOUDPUBLISH)){
            s_logger.debug("Cloud Publishing is enabled");
            if(m_capabilities.contains(asset)){
                s_logger.debug("ASSET " + asset + " is enabled");
                KuraPayload payload = new KuraPayload();
                payload.setTimestamp(new Date());
                payload.addMetric(asset, Integer.parseInt(value));
                try {
                    m_cloudClient.publish(m_pubTopic + "/" + id + "/" + asset, payload, 0, false);
                    s_logger.debug("message sent");
                } catch (Exception e) {
                    s_logger.error("Can't publish message, " + "keys", e);
                }
            }
            else{
                s_logger.debug("ASSET " + asset + " is disabled");
            }
        }
        else{
            s_logger.debug("Cloud Publishing is disabled");
        }
    }
}
