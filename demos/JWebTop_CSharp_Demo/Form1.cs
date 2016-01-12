using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using JWebTop;
using System.Threading;
namespace JWebTop_CSharp_Demo {
    public partial class MainForm : Form, WithinSwingCtrlHelper, JWebTopAppInited {

        // һ�������һ��������Ӧ������һ��JWebTopContext���ɣ�һ��JWebTopContext���Դ������Browser
        public JWebTopContext ctx = new JWebTopContext();
        private DemoBrowserCtrl ctrl = null;
        private JWebTopBrowser listBrowser = null;
        private JWebTopBrowser detailBrowser = null;
        public MainForm() {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e) {
            this.ctrl = new DemoBrowserCtrl();
            this.ctrl.setWithinSwingCtrlHelper(this);
            this.listBrowser = new JWebTopBrowser();
            this.detailBrowser = new JWebTopBrowser();

            ctx.setJsonHandler(this.ctrl);
            listBrowser.Dock = System.Windows.Forms.DockStyle.Fill;
            detailBrowser.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitMain.Panel1.Controls.Add(listBrowser);
            this.splitMain.Panel2.Controls.Add(detailBrowser);
            // ע�⣺һ��Ҫ�����߳��н��д���������������C#���������ѵ�Form.Load�¼��Ǵ�WndProc�з����ģ�Ȼ���JWebTopDLL��sendMessage��ͻ�ˣ�������
            Thread th = new Thread(new ThreadStart(createBrowser)); //Ҳ�ɼ�дΪnew Thread(ThreadMethod);                
            th.Start(); //�����߳�  
        }
        private void createBrowser() {
            string appFile = ctrl.getListAppFile();
            ctx.createJWebTopByCfgFile(ctrl.getJWebTopExe(), appFile, this);
        }
        public void onJWebTopAppInited() {
            jwebtopContextInited();
        }
        private class ListBrowserCreated : JWebTopBrowserCreated {
            private DemoBrowserCtrl ctrl = null;
            public ListBrowserCreated(DemoBrowserCtrl ctrl) { this.ctrl = ctrl; }
            public void onJWebTopBrowserCreated(int browserHWnd) {
                ctrl.setListHandler(browserHWnd);
            }
        }
        public void jwebtopContextInited() {
            string appFile = ctrl.getListAppFile();
            listBrowser.createInernalBrowser(ctx, appFile, null, "�б�ҳ", null, new ListBrowserCreated(ctrl));
        }
        private void btnNewNote_Click(object sender, EventArgs e) {
            string name = InputBox.ShowInputBox("����", "���������ƣ�");
            name = name.Trim();
            if (name.Length == 0) return;
            ctrl.addNote(name);
        }
        public JWebTopContext getCtx() {
            return this.ctx;
        }       
        private void btnDelNote_Click(object sender, EventArgs e) {
            string note = ctrl.getCurrentNote();
            if (note == null) return;
            if (MessageBox.Show(this, "�Ƿ�ɾ����" + note + "���ռǣ�") != DialogResult.OK) return;
            ctrl.delNote();
        }
        // �����java��ͬ��java��ֻ����㴰�ڲ��о����C#��ÿ���ռ䶼�о�������Է��ؿؼ��ļ��� 
        public int getMainHWnd() {
            return detailBrowser.getControlHandle();
        }
        public int[] getDetailRect() {
            Size s = detailBrowser.Size;
            return new int[] { 0, 0, s.Width, s.Height };
        }
        public void detailCreated(int browserHWnd) {
            detailBrowser.setBrowserHwnd(browserHWnd);
        }

        public void browserClosed(int browserHWnd) { }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e) {
          
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e) {
            ctx.closeContext();
        }
    }
}
