using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace windows_form_cs_1
{
    public partial class Form1 : Form
    {
        bool status_minimize = false;
        bool status_auto = false;
        string[] data;
        public Form1()
        {
            InitializeComponent();
        }
        
        private void Form1_Load(object sender, EventArgs e)
        {
            button4.Text = DateTime.Now.ToString("yyyy/MM/dd    HH:mm:ss");
            //讀取 data.txt 資料
            System.IO.StreamReader file = new System.IO.StreamReader("data.txt");
            string txt = file.ReadToEnd();
            file.Close();
            data = txt.Split('\n');
            textBox1.Text = "";
            for (int a = 1; a < data.Length; a++)
            {
                textBox1.Text += $"{data[a]}\n";
            }
            //列出本機目前有的COM
            string[] ports = SerialPort.GetPortNames();
            for (int a = 0; a < ports.Length; a++)
            {
                comboBox1.Items.Add(ports[a]);
                if (ports[a] == data[0].Trim())
                    comboBox1.Text = ports[a];
            }

        }
        void sendToArduino()
        {
            serialPort1.PortName = comboBox1.Text;
            serialPort1.Open();
            serialPort1.Write("Hello");
            serialPort1.Close();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (button1.Text.Equals("未啟動"))
            {
                button1.Text = "啟動中";
                status_auto = true;
            }
            else if (button1.Text.Equals("啟動中"))
            {
                button1.Text = "未啟動";
                status_auto = false;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.notifyIcon1.Icon = new Icon("arduino.ico");
            this.notifyIcon1.Text = "冷氣定時自啟控制台";
            this.WindowState = FormWindowState.Minimized;        //決定視窗大小
            this.ShowInTaskbar = false;                          //決定是否出現在工作列
            this.notifyIcon1.Visible = true;                     //決定使否顯示notifyIcon1
            status_minimize = true;
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            //在工具列點擊兩下，回復視窗
            if (e.Button == MouseButtons.Left)
            {
                button4.Text = DateTime.Now.ToString("yyyy/MM/dd    HH:mm:ss");
                this.Show();
                this.WindowState = FormWindowState.Normal;
                this.ShowInTaskbar = true;
                this.notifyIcon1.Visible = false;
                status_minimize = false;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            sendToArduino();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (!status_minimize)
                button4.Text = DateTime.Now.ToString("yyyy/MM/dd    HH:mm:ss");
            if (status_auto)
            {
                string time = DateTime.Now.ToString("HH:mm:ss");
                //System.Console.WriteLine(time);
                for (int a = 0; a < data.Length; a++)
                {
                    if (data[a].Trim() == time)
                    {
                        //System.Console.WriteLine("sendToArduino");
                        sendToArduino();
                    }
                }
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void button5_Click(object sender, EventArgs e)
        {
            System.IO.StreamWriter fileWriter = new System.IO.StreamWriter("data.txt");
            fileWriter.Write(comboBox1.Text + '\n' + textBox1.Text);
            fileWriter.Close();

            System.IO.StreamReader fileReader = new System.IO.StreamReader("data.txt");
            string txt = fileReader.ReadToEnd();
            fileReader.Close();
            data = txt.Split('\n');
            textBox1.Text = "";
            for (int a = 1; a < data.Length; a++)
                textBox1.Text += $"{data[a]}\n";

            //列出本機目前有的COM
            string[] ports = SerialPort.GetPortNames();
            for (int a = 0; a < ports.Length; a++)
            {
                comboBox1.Items.Add(ports[a]);
                if (ports[a] == data[0].Trim())
                    comboBox1.Text = ports[a];
            }
        }
    }
}
