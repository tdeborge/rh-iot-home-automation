package com.redhat.iot.gui;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;

import javax.swing.UIManager;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.StandardChartTheme;
import org.jfree.chart.plot.PiePlot;
import org.jfree.chart.title.TextTitle;
import org.jfree.data.general.DefaultPieDataset;
import org.jfree.data.general.PieDataset;
import org.jfree.ui.HorizontalAlignment;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.RectangleInsets;


public class LightStatsPie {
    
    JFreeChart chart;
    ChartPanel panel;
    DefaultPieDataset dataset;
    
    static {
        // set a theme using the new shadow generator feature available in
        // 1.0.14 - for backwards compatibility it is not enabled by default
        ChartFactory.setChartTheme(new StandardChartTheme("JFree/Shadow",
                true));
    }
    
    
    public LightStatsPie(){
        super();
        dataset = (DefaultPieDataset) createDataset();
        chart = createChart(dataset);
        chart.setPadding(new RectangleInsets(4, 8, 2, 2));
        panel = new ChartPanel(chart, false);
        panel.setMouseWheelEnabled(true);

    }
    
    private PieDataset createDataset() {
        DefaultPieDataset dataset = new DefaultPieDataset();
        dataset.setValue("ON", new Double(0));
        dataset.setValue("OFF", new Double(0));
        return dataset;
    }
    
    private JFreeChart createChart(PieDataset dataset) {

        JFreeChart chart = ChartFactory.createPieChart(
            HomeDashboard.getString("dashboard.graph.title"),  // chart title
            dataset,            // data
            false,              // no legend
            false,               // tooltips
            false               // no URL generation
        );

        // set a custom background for the chart
        chart.setBackgroundPaint(UIManager.getColor("Panel.background"));

        // customise the title position and font
        TextTitle t = chart.getTitle();
        t.setHorizontalAlignment(HorizontalAlignment.LEFT);
        //t.setPaint(new Color(240, 240, 240));
        t.setPaint(Color.BLACK);
        t.setFont(new Font("Arial", Font.BOLD, 20));

        PiePlot plot = (PiePlot) chart.getPlot();
        plot.setBackgroundPaint(null);
        plot.setInteriorGap(0.04);
        plot.setOutlineVisible(false);

        // use gradients and white borders for the section colours
//        plot.setSectionPaint("Others", createGradientPaint(new Color(200, 200, 255), Color.BLUE));
//        plot.setSectionPaint("Samsung", createGradientPaint(new Color(255, 200, 200), Color.RED));
//        plot.setSectionPaint("Apple", createGradientPaint(new Color(200, 255, 200), Color.GREEN));
//        plot.setSectionPaint("Nokia", createGradientPaint(new Color(200, 255, 200), Color.YELLOW));
        plot.setBaseSectionOutlinePaint(Color.BLACK);
        plot.setSectionOutlinesVisible(true);
        plot.setBaseSectionOutlineStroke(new BasicStroke(2.0f));

        // customise the section label appearance
        plot.setLabelFont(new Font("Courier New", Font.BOLD, 14));
        plot.setLabelLinkPaint(Color.BLACK);
        plot.setLabelLinkStroke(new BasicStroke(2.0f));
        plot.setLabelOutlineStroke(null);
        plot.setLabelPaint(Color.BLACK);
        plot.setLabelBackgroundPaint(null);
        
        // add a subtitle giving the data source
        TextTitle source = new TextTitle("IoT Demo on Wemos", 
                new Font("Courier New", Font.PLAIN, 14));
        source.setPaint(Color.BLACK);
        source.setPosition(RectangleEdge.BOTTOM);
        source.setHorizontalAlignment(HorizontalAlignment.RIGHT);
        chart.addSubtitle(source);
        return chart;
    }
   
    public JFreeChart getChart() {
        return chart;
    }

    
    public ChartPanel getPanel() {
        return panel;
    }
    
    public PieDataset getDataset() {
        return dataset;
    }
}
