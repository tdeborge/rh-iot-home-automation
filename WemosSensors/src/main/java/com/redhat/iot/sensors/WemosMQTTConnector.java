package com.redhat.iot.sensors;

import static org.eclipse.kura.camel.component.Configuration.asBoolean;
import static org.eclipse.kura.camel.component.Configuration.asString;

import java.util.LinkedHashMap;
import java.util.Map;

import org.apache.camel.CamelContext;
import org.apache.camel.builder.RouteBuilder;
import org.eclipse.kura.camel.cloud.KuraCloudComponent;
import org.eclipse.kura.camel.component.Configuration;
import org.eclipse.kura.camel.runner.CamelRunner;
import org.eclipse.kura.camel.runner.ServiceConsumer;
import org.eclipse.kura.cloud.CloudService;
import org.eclipse.kura.configuration.ConfigurableComponent;
import org.eclipse.kura.message.KuraPayload;
import org.fusesource.mqtt.client.MQTT;
import org.osgi.framework.BundleContext;
import org.osgi.framework.Constants;
import org.osgi.framework.FrameworkUtil;
import org.osgi.framework.InvalidSyntaxException;
import org.osgi.service.component.ComponentContext;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class WemosMQTTConnector implements ConfigurableComponent{
    
    private static final Logger s_logger = LoggerFactory.getLogger(WemosMQTTConnector.class);
    
    private String mBrokerURL;
    private String mUserName;
    private String mPassword;
    private String mSubTopic;
    private String mPubTopic;
    private boolean mScanEnabled = false;
    
    private CamelRunner camel;

    private String cloudServiceFilter;
    
    private Map<String, KuraPayload> payloads = new LinkedHashMap<>();

    /**
     * A RouterBuilder instance which has no routes
     */
    private static final RouteBuilder NO_ROUTES = new RouteBuilder() {

        @Override
        public void configure() throws Exception {
        }
    };
    
    protected void activate(ComponentContext context, Map<String, Object> properties)  throws Exception {
        s_logger.info("Wemos Component Activation Called");
        
        s_logger.info("Start: {}", properties);

        // create new filter and instance

        final String cloudServiceFilter = makeCloudServiceFilter(properties);
        this.camel = createCamelRunner(cloudServiceFilter);

        // set routes

        this.camel.setRoutes(fromProperties(properties));

        // start

        this.camel.start();
        
        
    }


    protected void deactivate(ComponentContext context) {
        s_logger.info("Wemos Component DE - Activation Called");
        if (this.camel != null) {
            this.camel.stop();
            this.camel = null;
        }
    }

    protected void updated(Map<String, Object> properties) throws Exception{
        s_logger.info("Wemos Component UPDATE Called");
        s_logger.info("Updating: {}", properties);

        final String cloudServiceFilter = makeCloudServiceFilter(properties);
        if (!this.cloudServiceFilter.equals(cloudServiceFilter)) {
            // update the routes and the filter

            // stop the camel context first
            this.camel.stop();

            // create a new camel runner, with new dependencies
            this.camel = createCamelRunner(cloudServiceFilter);

            // set the routes
            this.camel.setRoutes(fromProperties(properties));

            // and restart again
            this.camel.start();
        } else {
            // only update the routes, this is done without restarting the context

            this.camel.setRoutes(fromProperties(properties));
        }
    }

    private CamelRunner createCamelRunner(final String fullFilter) throws InvalidSyntaxException {
        final BundleContext ctx = FrameworkUtil.getBundle(WemosMQTTConnector.class).getBundleContext();

        this.cloudServiceFilter = fullFilter;

        // create a new camel CamelRunner.Builder

        final CamelRunner.Builder builder = new CamelRunner.Builder();

        // add service dependency

        builder.dependOn(ctx, FrameworkUtil.createFilter(fullFilter),
                new ServiceConsumer<CloudService, CamelContext>() {

                    @Override
                    public void consume(final CamelContext context, final CloudService service) {
                        context.addComponent("cloud", new KuraCloudComponent(context, service));
                    }
                });

        // return un-started instance

        return builder.build();
    }

    /**
     * Construct an OSGi filter for a cloud service instance
     *
     * @param properties
     *            the properties to read from
     * @return the OSGi filter selecting the cloud service instance
     */
    private static String makeCloudServiceFilter(final Map<String, Object> properties) {
        final String filterPid = Configuration.asStringNotEmpty(properties, "cloudService",
                "org.eclipse.kura.cloud.CloudService");
        final String fullFilter = String.format("(&(%s=%s)(kura.service.pid=%s))", Constants.OBJECTCLASS,
                CloudService.class.getName(), filterPid);
        return fullFilter;
    }

    /**
     * Create a new RouteBuilder instance from the properties
     *
     * @param properties
     *            the properties to read from
     * @return the new instance of RouteBuilder
     */
    protected RouteBuilder fromProperties(final Map<String, Object> properties) {

        if (!asBoolean(properties, "comms_enabled")) {
            s_logger.info("This Module has been disabled");
            return NO_ROUTES;
        }
        
        mBrokerURL = asString(properties, "BrokerURL");
        mUserName = asString(properties, "UserName");
        mPassword = asString(properties, "Password");
        mSubTopic = asString(properties, "SubscribingTopic");
        mPubTopic = asString(properties, "PublishingTopic");
 //       MQTT mqtt = new MQTT();

        // final int maxTemp = asInt(properties, "temperature.max", 20);

        return new RouteBuilder() {

            @Override
            public void configure() throws Exception {
                
//                from("timer://heartbeat?fixedRate=true&period=5000")
//                    .log("Timer started this route ")
//                    .log("BrokerURL: " + mBrokerURL)
//                    .log("Username: " + mUserName)
//                    .log("Password: " + mPassword)
//                    .log("Subscription: " + mSubTopic)
////                    .log("Publish: " +mPubTopic);
//                from("mqtt:wemosSensors?host=" + mBrokerURL +
//                                        "&userName=" + mUserName +
//                                        "&password=admin" +
//                                        "&subscribeTopicNames=" + mSubTopic)
                 from("paho:/Tim?brokerUrl=tcp://blah")
                    .log("Message Received on the Topic");
                
//                from(asString(properties, "filespec")).threads(12) // Poll for file and delete when finished
//                        .split().tokenize("\\n").streaming() // Process each line of the file separately, and stream to
//                                                             // keep memory usage down
//                        .delay(1000) // Delay 1 second between processing lines
//                        .log("Sending ${header.CamelSplitIndex} of ${header.CamelSplitSize}")
//                        .unmarshal(new CsvDataFormat().setIgnoreEmptyLines(true).setUseMaps(true).setCommentMarker('#')
//                                .setHeader(new String[] { "Ambient", "Light", "Humidity" }))
//                        .process(new Processor() {
//
//                            @Override
//                            public void process(Exchange exchange) throws Exception {
//                                KuraPayload payload = new KuraPayload();
//                                List<Map> metrics = (List<Map>) exchange.getIn().getBody();
//                                Map<String, String> map = metrics.get(0); // Each line of the file produces a map of
//                                                                          // name/value pairs, but we only get one line
//                                                                          // at a time due to the splitter above
//                                for (Map.Entry<String, String> entry : map.entrySet()) {
//                                    payload.addMetric(entry.getKey(), Float.parseFloat(entry.getValue()));
//                                }
//
//                                exchange.getIn().setBody(payload);
//                            }
//                        }).log("Sending CSV record")
//                        .toD("cloud:" + asString(properties, "topic.prefix") + "/assets/${file:name.noext}");

                // .to(KURA + TOPIC);
            }
        };
    }
    
    
}


//scan_enable
//BrokerURL
//UserName
//Password
//SubscribingTopic
//PublishingTopic