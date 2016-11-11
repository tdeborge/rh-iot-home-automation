package com.redhat.iot.gui;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.Toolkit;
import java.util.MissingResourceException;
import java.util.ResourceBundle;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redhat.iot.msg.DashboardMsgHandler;

public class HomeDashboard {

    private static final Logger s_logger = LoggerFactory.getLogger(HomeDashboard.class);

    public static final int WINDOW_WIDTH = 400;
    public static final int WINDOW_HEIGHT = 600;
    
    private JFrame window;
    private JLabel lbConnection, lbvConnection, lbMovement, lbvMovement, lbLight, lbvLight, lbNumSwitches, lbvNumSwitches, lbDuration, lbvDuration;

    private static ResourceBundle bundle = null;

    public static void main(String[] args) {
        HomeDashboard hd = new HomeDashboard();
        hd.initialize();
        hd.visualize();
        hd.startMessaging();       
    }

    private void startMessaging() {
        DashboardMsgHandler dbmh = new DashboardMsgHandler(this);
        dbmh.createMQTTConnection();
    }

    private void visualize() {
        window.setVisible(true);
    }

    private void initialize() {
        s_logger.info("Starting the application");
        s_logger.info("Getting the first parameter: " + getString("dashboard.author"));
        
        window = new JFrame(getString("dashboard.window.title"));
        //window.setIconImage(new ImageIcon(getClass().getResource(getString("DSCleanerApp.window.icon.image"))).getImage());
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.getContentPane().setLayout(null);
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        window.setResizable(false);
        window.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        window.setLocation(screenSize.width / 2 - window.getSize().width / 2, screenSize.height / 2
            - window.getSize().height / 2);
        
        createLabels();
        window.add(lbConnection);
        window.add(lbMovement);
        window.add(lbLight);
        window.add(lbNumSwitches);
        window.add(lbDuration);
        createvLabels();
        window.add(lbvConnection);
        window.add(lbvMovement);
        window.add(lbvLight);
        window.add(lbvNumSwitches);
        window.add(lbvDuration);
        
        addSeparators();
             
    }

    private void addSeparators() {
        JSeparator seph1 = new JSeparator(SwingConstants.HORIZONTAL);
        seph1.setBounds(0,45,400,10);
        seph1.setVisible(true);
        seph1.setForeground(java.awt.Color.BLUE);
        seph1.setEnabled(true);
        seph1.setOpaque(true);
        window.add(seph1);
        
        JSeparator seph2 = new JSeparator(SwingConstants.HORIZONTAL);
        seph2.setBounds(0,95,400,10);
        seph2.setVisible(true);
        seph2.setForeground(java.awt.Color.BLUE);
        seph2.setEnabled(true);
        seph2.setOpaque(true);
        window.add(seph2);
        
        JSeparator seph3 = new JSeparator(SwingConstants.HORIZONTAL);
        seph3.setBounds(0,145,400,10);
        seph3.setVisible(true);
        seph3.setForeground(java.awt.Color.BLUE);
        seph3.setEnabled(true);
        seph3.setOpaque(true);
        window.add(seph3);
        
        JSeparator seph4 = new JSeparator(SwingConstants.HORIZONTAL);
        seph4.setBounds(0,195,400,10);
        seph4.setVisible(true);
        seph4.setForeground(java.awt.Color.BLUE);
        seph4.setEnabled(true);
        seph4.setOpaque(true);
        window.add(seph4);
        
        JSeparator sepv = new JSeparator(SwingConstants.VERTICAL);
        sepv.setBounds(270,0,10,600);
        sepv.setVisible(true);
        sepv.setForeground(java.awt.Color.BLUE);
        sepv.setEnabled(true);
        sepv.setOpaque(true);
        window.add(sepv);         
    }

    private void createLabels() {
        lbConnection = new JLabel(getString("dashboard.window.label.connection"));
        lbConnection.setForeground(java.awt.Color.black);
        lbConnection.setFont(new Font("Dialog", Font.BOLD, 24));
        lbConnection.setBounds(15, 530, 265, 25);
        lbConnection.setHorizontalTextPosition(SwingConstants.LEFT);
        lbConnection.setVisible(true);
        
        lbMovement = new JLabel(getString("dashboard.window.label.movement"));
        lbMovement.setForeground(java.awt.Color.black);
        lbMovement.setFont(new Font("Dialog", Font.BOLD, 24));
        lbMovement.setBounds(15, 15, 265, 25);
        lbMovement.setHorizontalTextPosition(SwingConstants.LEFT);
        lbMovement.setVisible(true);
        
        lbLight = new JLabel(getString("dashboard.window.label.light"));
        lbLight.setForeground(java.awt.Color.black);
        lbLight.setFont(new Font("Dialog", Font.BOLD, 24));
        lbLight.setBounds(15, 65, 265, 25);
        lbLight.setHorizontalTextPosition(SwingConstants.LEFT);
        lbLight.setVisible(true);
        
        lbNumSwitches = new JLabel(getString("dashboard.window.label.switchcount"));
        lbNumSwitches.setForeground(java.awt.Color.black);
        lbNumSwitches.setFont(new Font("Dialog", Font.BOLD, 24));
        lbNumSwitches.setBounds(15, 115, 265, 25);
        lbNumSwitches.setHorizontalTextPosition(SwingConstants.LEFT);
        lbNumSwitches.setVisible(true);
        
        lbDuration = new JLabel(getString("dashboard.window.label.lightdetatils"));
        lbDuration.setForeground(java.awt.Color.black);
        lbDuration.setFont(new Font("Dialog", Font.BOLD, 24));
        lbDuration.setBounds(15, 165, 265, 25);
        lbDuration.setHorizontalTextPosition(SwingConstants.LEFT);
        lbNumSwitches.setVisible(true);
        
    }

    private void createvLabels() {
        lbvConnection = new JLabel();
        lbvConnection.setBackground(java.awt.Color.red);
        lbvConnection.setOpaque(true);
        lbvConnection.setBounds(315,530,40,25);
        lbvConnection.setHorizontalTextPosition(SwingConstants.RIGHT);
        lbvConnection.setVisible(true);
        
        lbvMovement = new JLabel("-----");
        lbvMovement.setForeground(java.awt.Color.black);
        lbvMovement.setFont(new Font("Dialog", Font.BOLD, 24));
        lbvMovement.setBounds(290, 15, 300, 25);
        lbvMovement.setHorizontalTextPosition(SwingConstants.RIGHT);
        lbvMovement.setVisible(true);
        
        lbvLight = new JLabel("-----");
        lbvLight.setForeground(java.awt.Color.black);
        lbvLight.setFont(new Font("Dialog", Font.BOLD, 24));
        lbvLight.setBounds(290, 65, 300, 25);
        lbvLight.setHorizontalTextPosition(SwingConstants.RIGHT);
        lbvLight.setVisible(true);
        
        lbvNumSwitches = new JLabel("-----");
        lbvNumSwitches.setForeground(java.awt.Color.black);
        lbvNumSwitches.setFont(new Font("Dialog", Font.BOLD, 24));
        lbvNumSwitches.setBounds(290, 115, 300, 25);
        lbvNumSwitches.setHorizontalTextPosition(SwingConstants.RIGHT);
        lbvNumSwitches.setText("100000");
        lbvNumSwitches.setVisible(true);

        lbvDuration = new JLabel("-----");
        lbvDuration.setForeground(java.awt.Color.black);
        lbvDuration.setFont(new Font("Dialog", Font.BOLD, 24));
        lbvDuration.setBounds(290, 165, 300, 25);
        lbvDuration.setHorizontalTextPosition(SwingConstants.RIGHT);
        lbvDuration.setVisible(true);        
    }

    public static String getString(String key) {
        String value = null;
        try {
            value = getResourceBundle().getString(key);
        } catch (MissingResourceException e) {
            System.out.println("java.util.MissingResourceException: Couldn't find value for: " + key);
        }
        if (value == null) {
            value = "Could not find resource: " + key + "  ";
        }
        return value;
    }

    public static ResourceBundle getResourceBundle() {
        s_logger.debug("Setting the Resource Bundle");
        while (bundle == null) {
          try {
            bundle = ResourceBundle.getBundle("resources.dashboard");
          } catch (java.util.MissingResourceException e) {
            e.printStackTrace();
            System.exit(10);
          }
        }
        return bundle;
    }

    public void setConnectSuccess() {
        lbvConnection.setBackground(java.awt.Color.green);
        lbvConnection.validate();
    }
    public void setConnectFailed() {
        lbvConnection.setBackground(java.awt.Color.red);
        lbvConnection.validate();
    }

    public void setTickerValues(long moveTick, long lightTime, long lightTick, boolean lightOn) {
        lbvMovement.setText("" + moveTick);
        if(lightOn){
            lbvLight.setText("ON");
        }
        else{
            lbvLight.setText("OFF");
        }       
        lbvNumSwitches.setText("" + lightTick);
        lbvDuration.setText("" + lightTime);
        window.validate();
    }
}
