
namespace OptimizerGUI
{
    partial class Form1
    {
        /// <summary>
        /// Vyžaduje se proměnná návrháře.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Uvolněte všechny používané prostředky.
        /// </summary>
        /// <param name="disposing">hodnota true, když by se měl spravovaný prostředek odstranit; jinak false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kód generovaný Návrhářem Windows Form

        /// <summary>
        /// Metoda vyžadovaná pro podporu Návrháře - neupravovat
        /// obsah této metody v editoru kódu.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonApply = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPageSettings = new System.Windows.Forms.TabPage();
            this.buttonModifyPowershell = new System.Windows.Forms.Button();
            this.groupBoxOptimizer = new System.Windows.Forms.GroupBox();
            this.checkedListBoxOptimizer = new System.Windows.Forms.CheckedListBox();
            this.groupBoxSystem = new System.Windows.Forms.GroupBox();
            this.checkedListBoxOS = new System.Windows.Forms.CheckedListBox();
            this.groupBoxServices = new System.Windows.Forms.GroupBox();
            this.checkedListBoxServices = new System.Windows.Forms.CheckedListBox();
            this.buttonModifyServices = new System.Windows.Forms.Button();
            this.tabPageProcesses = new System.Windows.Forms.TabPage();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.checkBoxLowerProcesses = new System.Windows.Forms.CheckBox();
            this.richTextBoxLowerPriority = new System.Windows.Forms.RichTextBox();
            this.groupBoxFreezeProcesses = new System.Windows.Forms.GroupBox();
            this.richTextBoxFreeze = new System.Windows.Forms.RichTextBox();
            this.groupBoxStopProcesses = new System.Windows.Forms.GroupBox();
            this.checkBoxDisableDesktop = new System.Windows.Forms.CheckBox();
            this.richTextBoxStop = new System.Windows.Forms.RichTextBox();
            this.tabPageTasks = new System.Windows.Forms.TabPage();
            this.groupBoxPriority = new System.Windows.Forms.GroupBox();
            this.radioButtonHigh = new System.Windows.Forms.RadioButton();
            this.radioButtonAbove = new System.Windows.Forms.RadioButton();
            this.radioButtonNormal = new System.Windows.Forms.RadioButton();
            this.radioButtonBelow = new System.Windows.Forms.RadioButton();
            this.buttonAddAutorun = new System.Windows.Forms.Button();
            this.richTextBoxAutorun = new System.Windows.Forms.RichTextBox();
            this.buttonSaveConfig = new System.Windows.Forms.Button();
            this.buttonViewConfig = new System.Windows.Forms.Button();
            this.groupBoxApplyConfig = new System.Windows.Forms.GroupBox();
            this.buttonReloadConfig = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.buttonCreateRestorePoint = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.groupBoxRestore = new System.Windows.Forms.GroupBox();
            this.buttonRestore = new System.Windows.Forms.Button();
            this.buttonResume = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabPageSettings.SuspendLayout();
            this.groupBoxOptimizer.SuspendLayout();
            this.groupBoxSystem.SuspendLayout();
            this.groupBoxServices.SuspendLayout();
            this.tabPageProcesses.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBoxFreezeProcesses.SuspendLayout();
            this.groupBoxStopProcesses.SuspendLayout();
            this.tabPageTasks.SuspendLayout();
            this.groupBoxPriority.SuspendLayout();
            this.groupBoxApplyConfig.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBoxRestore.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(246, 81);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(93, 35);
            this.buttonSave.TabIndex = 0;
            this.buttonSave.Text = "Save config";
            this.buttonSave.UseVisualStyleBackColor = true;
            // 
            // buttonApply
            // 
            this.buttonApply.Location = new System.Drawing.Point(6, 115);
            this.buttonApply.Name = "buttonApply";
            this.buttonApply.Size = new System.Drawing.Size(81, 26);
            this.buttonApply.TabIndex = 1;
            this.buttonApply.Text = "Apply";
            this.buttonApply.UseVisualStyleBackColor = true;
            this.buttonApply.Click += new System.EventHandler(this.buttonApply_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPageSettings);
            this.tabControl1.Controls.Add(this.tabPageProcesses);
            this.tabControl1.Controls.Add(this.tabPageTasks);
            this.tabControl1.Location = new System.Drawing.Point(13, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(227, 383);
            this.tabControl1.TabIndex = 3;
            // 
            // tabPageSettings
            // 
            this.tabPageSettings.Controls.Add(this.buttonModifyPowershell);
            this.tabPageSettings.Controls.Add(this.groupBoxOptimizer);
            this.tabPageSettings.Controls.Add(this.groupBoxSystem);
            this.tabPageSettings.Controls.Add(this.groupBoxServices);
            this.tabPageSettings.Controls.Add(this.buttonModifyServices);
            this.tabPageSettings.Location = new System.Drawing.Point(4, 22);
            this.tabPageSettings.Name = "tabPageSettings";
            this.tabPageSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageSettings.Size = new System.Drawing.Size(219, 357);
            this.tabPageSettings.TabIndex = 0;
            this.tabPageSettings.Text = "Settings";
            this.tabPageSettings.UseVisualStyleBackColor = true;
            // 
            // buttonModifyPowershell
            // 
            this.buttonModifyPowershell.Location = new System.Drawing.Point(127, 316);
            this.buttonModifyPowershell.Name = "buttonModifyPowershell";
            this.buttonModifyPowershell.Size = new System.Drawing.Size(83, 34);
            this.buttonModifyPowershell.TabIndex = 9;
            this.buttonModifyPowershell.Text = "Modify OS scripts";
            this.buttonModifyPowershell.UseVisualStyleBackColor = true;
            this.buttonModifyPowershell.Click += new System.EventHandler(this.buttonModifyPowershell_Click);
            // 
            // groupBoxOptimizer
            // 
            this.groupBoxOptimizer.Controls.Add(this.checkedListBoxOptimizer);
            this.groupBoxOptimizer.Location = new System.Drawing.Point(6, 111);
            this.groupBoxOptimizer.Name = "groupBoxOptimizer";
            this.groupBoxOptimizer.Size = new System.Drawing.Size(204, 115);
            this.groupBoxOptimizer.TabIndex = 3;
            this.groupBoxOptimizer.TabStop = false;
            this.groupBoxOptimizer.Text = "Optimizer settings";
            // 
            // checkedListBoxOptimizer
            // 
            this.checkedListBoxOptimizer.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.checkedListBoxOptimizer.CheckOnClick = true;
            this.checkedListBoxOptimizer.FormattingEnabled = true;
            this.checkedListBoxOptimizer.Items.AddRange(new object[] {
            "No permanent changes",
            "Create a services restore file",
            "Auto apply config on user logon",
            "Auto start GUI on user logon",
            "Quiet output",
            "Exit after applying"});
            this.checkedListBoxOptimizer.Location = new System.Drawing.Point(6, 19);
            this.checkedListBoxOptimizer.Name = "checkedListBoxOptimizer";
            this.checkedListBoxOptimizer.Size = new System.Drawing.Size(192, 90);
            this.checkedListBoxOptimizer.TabIndex = 0;
            // 
            // groupBoxSystem
            // 
            this.groupBoxSystem.Controls.Add(this.checkedListBoxOS);
            this.groupBoxSystem.Location = new System.Drawing.Point(6, 230);
            this.groupBoxSystem.Name = "groupBoxSystem";
            this.groupBoxSystem.Size = new System.Drawing.Size(204, 80);
            this.groupBoxSystem.TabIndex = 2;
            this.groupBoxSystem.TabStop = false;
            this.groupBoxSystem.Text = "OS Settings";
            // 
            // checkedListBoxOS
            // 
            this.checkedListBoxOS.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.checkedListBoxOS.CheckOnClick = true;
            this.checkedListBoxOS.FormattingEnabled = true;
            this.checkedListBoxOS.Items.AddRange(new object[] {
            "Run OS tweaks",
            "Turn off Windows defender",
            "Turn off Windows firewall",
            "Uninstall default Windows Apps"});
            this.checkedListBoxOS.Location = new System.Drawing.Point(5, 14);
            this.checkedListBoxOS.Name = "checkedListBoxOS";
            this.checkedListBoxOS.Size = new System.Drawing.Size(193, 60);
            this.checkedListBoxOS.TabIndex = 0;
            this.checkedListBoxOS.SelectedIndexChanged += new System.EventHandler(this.checkedListBoxOS_SelectedIndexChanged);
            // 
            // groupBoxServices
            // 
            this.groupBoxServices.Controls.Add(this.checkedListBoxServices);
            this.groupBoxServices.Location = new System.Drawing.Point(6, 6);
            this.groupBoxServices.Name = "groupBoxServices";
            this.groupBoxServices.Size = new System.Drawing.Size(205, 99);
            this.groupBoxServices.TabIndex = 1;
            this.groupBoxServices.TabStop = false;
            this.groupBoxServices.Text = "Services";
            // 
            // checkedListBoxServices
            // 
            this.checkedListBoxServices.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.checkedListBoxServices.CheckOnClick = true;
            this.checkedListBoxServices.FormattingEnabled = true;
            this.checkedListBoxServices.Items.AddRange(new object[] {
            "Disable all internet",
            "Disable wireless internet",
            "Disable Bluetooth",
            "Disable audio",
            "I am using a laptop"});
            this.checkedListBoxServices.Location = new System.Drawing.Point(6, 15);
            this.checkedListBoxServices.Name = "checkedListBoxServices";
            this.checkedListBoxServices.Size = new System.Drawing.Size(193, 75);
            this.checkedListBoxServices.TabIndex = 0;
            // 
            // buttonModifyServices
            // 
            this.buttonModifyServices.Location = new System.Drawing.Point(6, 316);
            this.buttonModifyServices.Name = "buttonModifyServices";
            this.buttonModifyServices.Size = new System.Drawing.Size(83, 34);
            this.buttonModifyServices.TabIndex = 6;
            this.buttonModifyServices.Text = "Modify list of services";
            this.buttonModifyServices.UseVisualStyleBackColor = true;
            this.buttonModifyServices.Click += new System.EventHandler(this.buttonModifyServices_Click);
            // 
            // tabPageProcesses
            // 
            this.tabPageProcesses.Controls.Add(this.groupBox3);
            this.tabPageProcesses.Controls.Add(this.groupBoxFreezeProcesses);
            this.tabPageProcesses.Controls.Add(this.groupBoxStopProcesses);
            this.tabPageProcesses.Location = new System.Drawing.Point(4, 22);
            this.tabPageProcesses.Name = "tabPageProcesses";
            this.tabPageProcesses.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageProcesses.Size = new System.Drawing.Size(219, 357);
            this.tabPageProcesses.TabIndex = 1;
            this.tabPageProcesses.Text = "Processes";
            this.tabPageProcesses.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.checkBoxLowerProcesses);
            this.groupBox3.Controls.Add(this.richTextBoxLowerPriority);
            this.groupBox3.Location = new System.Drawing.Point(6, 246);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(206, 108);
            this.groupBox3.TabIndex = 4;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Lower priority";
            // 
            // checkBoxLowerProcesses
            // 
            this.checkBoxLowerProcesses.AutoSize = true;
            this.checkBoxLowerProcesses.Location = new System.Drawing.Point(6, 19);
            this.checkBoxLowerProcesses.Name = "checkBoxLowerProcesses";
            this.checkBoxLowerProcesses.Size = new System.Drawing.Size(195, 17);
            this.checkBoxLowerProcesses.TabIndex = 1;
            this.checkBoxLowerProcesses.Text = "Lower non-critical system processes";
            this.checkBoxLowerProcesses.UseVisualStyleBackColor = true;
            this.checkBoxLowerProcesses.CheckedChanged += new System.EventHandler(this.checkBoxLowerProcesses_CheckedChanged);
            // 
            // richTextBoxLowerPriority
            // 
            this.richTextBoxLowerPriority.Location = new System.Drawing.Point(6, 42);
            this.richTextBoxLowerPriority.Name = "richTextBoxLowerPriority";
            this.richTextBoxLowerPriority.Size = new System.Drawing.Size(193, 62);
            this.richTextBoxLowerPriority.TabIndex = 0;
            this.richTextBoxLowerPriority.Text = "";
            // 
            // groupBoxFreezeProcesses
            // 
            this.groupBoxFreezeProcesses.Controls.Add(this.richTextBoxFreeze);
            this.groupBoxFreezeProcesses.Location = new System.Drawing.Point(7, 139);
            this.groupBoxFreezeProcesses.Name = "groupBoxFreezeProcesses";
            this.groupBoxFreezeProcesses.Size = new System.Drawing.Size(206, 101);
            this.groupBoxFreezeProcesses.TabIndex = 3;
            this.groupBoxFreezeProcesses.TabStop = false;
            this.groupBoxFreezeProcesses.Text = "Freeze";
            // 
            // richTextBoxFreeze
            // 
            this.richTextBoxFreeze.Location = new System.Drawing.Point(6, 19);
            this.richTextBoxFreeze.Name = "richTextBoxFreeze";
            this.richTextBoxFreeze.Size = new System.Drawing.Size(194, 76);
            this.richTextBoxFreeze.TabIndex = 0;
            this.richTextBoxFreeze.Text = "RuntimeBroker.exe";
            // 
            // groupBoxStopProcesses
            // 
            this.groupBoxStopProcesses.Controls.Add(this.checkBoxDisableDesktop);
            this.groupBoxStopProcesses.Controls.Add(this.richTextBoxStop);
            this.groupBoxStopProcesses.Location = new System.Drawing.Point(7, 6);
            this.groupBoxStopProcesses.Name = "groupBoxStopProcesses";
            this.groupBoxStopProcesses.Size = new System.Drawing.Size(206, 127);
            this.groupBoxStopProcesses.TabIndex = 2;
            this.groupBoxStopProcesses.TabStop = false;
            this.groupBoxStopProcesses.Text = "Stop";
            // 
            // checkBoxDisableDesktop
            // 
            this.checkBoxDisableDesktop.AutoSize = true;
            this.checkBoxDisableDesktop.Checked = true;
            this.checkBoxDisableDesktop.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxDisableDesktop.Location = new System.Drawing.Point(9, 14);
            this.checkBoxDisableDesktop.Name = "checkBoxDisableDesktop";
            this.checkBoxDisableDesktop.Size = new System.Drawing.Size(181, 17);
            this.checkBoxDisableDesktop.TabIndex = 1;
            this.checkBoxDisableDesktop.Text = "Disable the desktop environment";
            this.checkBoxDisableDesktop.UseVisualStyleBackColor = true;
            this.checkBoxDisableDesktop.CheckedChanged += new System.EventHandler(this.checkBoxDisableDesktop_CheckedChanged);
            // 
            // richTextBoxStop
            // 
            this.richTextBoxStop.DetectUrls = false;
            this.richTextBoxStop.Location = new System.Drawing.Point(6, 37);
            this.richTextBoxStop.Name = "richTextBoxStop";
            this.richTextBoxStop.Size = new System.Drawing.Size(194, 84);
            this.richTextBoxStop.TabIndex = 0;
            this.richTextBoxStop.Text = "explorer.exe\ndwm.exe\nCompatTelRunner.exe\nOfficeClickToRun.exe";
            // 
            // tabPageTasks
            // 
            this.tabPageTasks.Controls.Add(this.groupBoxPriority);
            this.tabPageTasks.Controls.Add(this.buttonAddAutorun);
            this.tabPageTasks.Controls.Add(this.richTextBoxAutorun);
            this.tabPageTasks.Location = new System.Drawing.Point(4, 22);
            this.tabPageTasks.Name = "tabPageTasks";
            this.tabPageTasks.Size = new System.Drawing.Size(219, 357);
            this.tabPageTasks.TabIndex = 2;
            this.tabPageTasks.Text = "Autorun";
            this.tabPageTasks.UseVisualStyleBackColor = true;
            // 
            // groupBoxPriority
            // 
            this.groupBoxPriority.Controls.Add(this.radioButtonHigh);
            this.groupBoxPriority.Controls.Add(this.radioButtonAbove);
            this.groupBoxPriority.Controls.Add(this.radioButtonNormal);
            this.groupBoxPriority.Controls.Add(this.radioButtonBelow);
            this.groupBoxPriority.Location = new System.Drawing.Point(6, 4);
            this.groupBoxPriority.Name = "groupBoxPriority";
            this.groupBoxPriority.Size = new System.Drawing.Size(100, 94);
            this.groupBoxPriority.TabIndex = 2;
            this.groupBoxPriority.TabStop = false;
            this.groupBoxPriority.Text = "Priority";
            // 
            // radioButtonHigh
            // 
            this.radioButtonHigh.AutoSize = true;
            this.radioButtonHigh.Location = new System.Drawing.Point(6, 70);
            this.radioButtonHigh.Name = "radioButtonHigh";
            this.radioButtonHigh.Size = new System.Drawing.Size(47, 17);
            this.radioButtonHigh.TabIndex = 3;
            this.radioButtonHigh.Text = "High";
            this.radioButtonHigh.UseVisualStyleBackColor = true;
            // 
            // radioButtonAbove
            // 
            this.radioButtonAbove.AutoSize = true;
            this.radioButtonAbove.Location = new System.Drawing.Point(6, 53);
            this.radioButtonAbove.Name = "radioButtonAbove";
            this.radioButtonAbove.Size = new System.Drawing.Size(90, 17);
            this.radioButtonAbove.TabIndex = 2;
            this.radioButtonAbove.Text = "Above normal";
            this.radioButtonAbove.UseVisualStyleBackColor = true;
            // 
            // radioButtonNormal
            // 
            this.radioButtonNormal.AutoSize = true;
            this.radioButtonNormal.Checked = true;
            this.radioButtonNormal.Location = new System.Drawing.Point(6, 37);
            this.radioButtonNormal.Name = "radioButtonNormal";
            this.radioButtonNormal.Size = new System.Drawing.Size(58, 17);
            this.radioButtonNormal.TabIndex = 1;
            this.radioButtonNormal.TabStop = true;
            this.radioButtonNormal.Text = "Normal";
            this.radioButtonNormal.UseVisualStyleBackColor = true;
            // 
            // radioButtonBelow
            // 
            this.radioButtonBelow.AutoSize = true;
            this.radioButtonBelow.Location = new System.Drawing.Point(6, 19);
            this.radioButtonBelow.Name = "radioButtonBelow";
            this.radioButtonBelow.Size = new System.Drawing.Size(88, 17);
            this.radioButtonBelow.TabIndex = 0;
            this.radioButtonBelow.Text = "Below normal";
            this.radioButtonBelow.UseVisualStyleBackColor = true;
            // 
            // buttonAddAutorun
            // 
            this.buttonAddAutorun.Location = new System.Drawing.Point(118, 5);
            this.buttonAddAutorun.Name = "buttonAddAutorun";
            this.buttonAddAutorun.Size = new System.Drawing.Size(96, 94);
            this.buttonAddAutorun.TabIndex = 1;
            this.buttonAddAutorun.Text = "Add an executable";
            this.buttonAddAutorun.UseVisualStyleBackColor = true;
            this.buttonAddAutorun.Click += new System.EventHandler(this.buttonAddAutorun_Click);
            // 
            // richTextBoxAutorun
            // 
            this.richTextBoxAutorun.DetectUrls = false;
            this.richTextBoxAutorun.Location = new System.Drawing.Point(3, 104);
            this.richTextBoxAutorun.Name = "richTextBoxAutorun";
            this.richTextBoxAutorun.Size = new System.Drawing.Size(213, 249);
            this.richTextBoxAutorun.TabIndex = 0;
            this.richTextBoxAutorun.Text = "";
            this.richTextBoxAutorun.WordWrap = false;
            // 
            // buttonSaveConfig
            // 
            this.buttonSaveConfig.Location = new System.Drawing.Point(6, 19);
            this.buttonSaveConfig.Name = "buttonSaveConfig";
            this.buttonSaveConfig.Size = new System.Drawing.Size(81, 26);
            this.buttonSaveConfig.TabIndex = 10;
            this.buttonSaveConfig.Text = "Save";
            this.buttonSaveConfig.UseVisualStyleBackColor = true;
            this.buttonSaveConfig.Click += new System.EventHandler(this.buttonSaveConfig_Click);
            // 
            // buttonViewConfig
            // 
            this.buttonViewConfig.Location = new System.Drawing.Point(6, 51);
            this.buttonViewConfig.Name = "buttonViewConfig";
            this.buttonViewConfig.Size = new System.Drawing.Size(81, 26);
            this.buttonViewConfig.TabIndex = 11;
            this.buttonViewConfig.Text = "View";
            this.buttonViewConfig.UseVisualStyleBackColor = true;
            this.buttonViewConfig.Click += new System.EventHandler(this.buttonViewConfig_Click);
            // 
            // groupBoxApplyConfig
            // 
            this.groupBoxApplyConfig.Controls.Add(this.buttonReloadConfig);
            this.groupBoxApplyConfig.Controls.Add(this.buttonSaveConfig);
            this.groupBoxApplyConfig.Controls.Add(this.buttonViewConfig);
            this.groupBoxApplyConfig.Controls.Add(this.buttonApply);
            this.groupBoxApplyConfig.Location = new System.Drawing.Point(246, 19);
            this.groupBoxApplyConfig.Name = "groupBoxApplyConfig";
            this.groupBoxApplyConfig.Size = new System.Drawing.Size(93, 152);
            this.groupBoxApplyConfig.TabIndex = 13;
            this.groupBoxApplyConfig.TabStop = false;
            this.groupBoxApplyConfig.Text = "Config";
            // 
            // buttonReloadConfig
            // 
            this.buttonReloadConfig.Location = new System.Drawing.Point(6, 83);
            this.buttonReloadConfig.Name = "buttonReloadConfig";
            this.buttonReloadConfig.Size = new System.Drawing.Size(81, 26);
            this.buttonReloadConfig.TabIndex = 12;
            this.buttonReloadConfig.Text = "Reload";
            this.buttonReloadConfig.UseVisualStyleBackColor = true;
            this.buttonReloadConfig.Click += new System.EventHandler(this.buttonReloadConfig_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.buttonCreateRestorePoint);
            this.groupBox2.Location = new System.Drawing.Point(246, 303);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(93, 81);
            this.groupBox2.TabIndex = 15;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Advanced";
            // 
            // buttonCreateRestorePoint
            // 
            this.buttonCreateRestorePoint.Location = new System.Drawing.Point(6, 19);
            this.buttonCreateRestorePoint.Name = "buttonCreateRestorePoint";
            this.buttonCreateRestorePoint.Size = new System.Drawing.Size(81, 53);
            this.buttonCreateRestorePoint.TabIndex = 8;
            this.buttonCreateRestorePoint.Text = "Create a system restore point";
            this.buttonCreateRestorePoint.UseVisualStyleBackColor = true;
            this.buttonCreateRestorePoint.Click += new System.EventHandler(this.buttonCreateRestorePoint_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "file";
            this.openFileDialog1.Title = "Choose a file to start after applying config";
            // 
            // groupBoxRestore
            // 
            this.groupBoxRestore.Controls.Add(this.buttonRestore);
            this.groupBoxRestore.Controls.Add(this.buttonResume);
            this.groupBoxRestore.Location = new System.Drawing.Point(246, 177);
            this.groupBoxRestore.Name = "groupBoxRestore";
            this.groupBoxRestore.Size = new System.Drawing.Size(93, 126);
            this.groupBoxRestore.TabIndex = 16;
            this.groupBoxRestore.TabStop = false;
            this.groupBoxRestore.Text = "Restore";
            // 
            // buttonRestore
            // 
            this.buttonRestore.Location = new System.Drawing.Point(6, 68);
            this.buttonRestore.Name = "buttonRestore";
            this.buttonRestore.Size = new System.Drawing.Size(81, 52);
            this.buttonRestore.TabIndex = 1;
            this.buttonRestore.Text = "Resume + restore services";
            this.buttonRestore.UseVisualStyleBackColor = true;
            this.buttonRestore.Click += new System.EventHandler(this.buttonRestore_Click);
            // 
            // buttonResume
            // 
            this.buttonResume.Location = new System.Drawing.Point(6, 19);
            this.buttonResume.Name = "buttonResume";
            this.buttonResume.Size = new System.Drawing.Size(81, 43);
            this.buttonResume.TabIndex = 0;
            this.buttonResume.Text = "Resume processes";
            this.buttonResume.UseVisualStyleBackColor = true;
            this.buttonResume.Click += new System.EventHandler(this.buttonResume_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(351, 401);
            this.Controls.Add(this.groupBoxRestore);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBoxApplyConfig);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.buttonSave);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Windows Real Time Optimizer";
            this.tabControl1.ResumeLayout(false);
            this.tabPageSettings.ResumeLayout(false);
            this.groupBoxOptimizer.ResumeLayout(false);
            this.groupBoxSystem.ResumeLayout(false);
            this.groupBoxServices.ResumeLayout(false);
            this.tabPageProcesses.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBoxFreezeProcesses.ResumeLayout(false);
            this.groupBoxStopProcesses.ResumeLayout(false);
            this.groupBoxStopProcesses.PerformLayout();
            this.tabPageTasks.ResumeLayout(false);
            this.groupBoxPriority.ResumeLayout(false);
            this.groupBoxPriority.PerformLayout();
            this.groupBoxApplyConfig.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBoxRestore.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonApply;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPageSettings;
        private System.Windows.Forms.GroupBox groupBoxServices;
        private System.Windows.Forms.CheckedListBox checkedListBoxServices;
        private System.Windows.Forms.TabPage tabPageProcesses;
        private System.Windows.Forms.TabPage tabPageTasks;
        private System.Windows.Forms.GroupBox groupBoxSystem;
        private System.Windows.Forms.CheckedListBox checkedListBoxOS;
        private System.Windows.Forms.GroupBox groupBoxOptimizer;
        private System.Windows.Forms.CheckedListBox checkedListBoxOptimizer;
        private System.Windows.Forms.Button buttonModifyServices;
        private System.Windows.Forms.RichTextBox richTextBoxStop;
        private System.Windows.Forms.Button buttonSaveConfig;
        private System.Windows.Forms.Button buttonViewConfig;
        private System.Windows.Forms.GroupBox groupBoxApplyConfig;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonCreateRestorePoint;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBoxFreezeProcesses;
        private System.Windows.Forms.RichTextBox richTextBoxFreeze;
        private System.Windows.Forms.GroupBox groupBoxStopProcesses;
        private System.Windows.Forms.CheckBox checkBoxLowerProcesses;
        private System.Windows.Forms.RichTextBox richTextBoxLowerPriority;
        private System.Windows.Forms.CheckBox checkBoxDisableDesktop;
        private System.Windows.Forms.Button buttonReloadConfig;
        private System.Windows.Forms.Button buttonAddAutorun;
        private System.Windows.Forms.RichTextBox richTextBoxAutorun;
        private System.Windows.Forms.Button buttonModifyPowershell;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.GroupBox groupBoxPriority;
        private System.Windows.Forms.RadioButton radioButtonHigh;
        private System.Windows.Forms.RadioButton radioButtonAbove;
        private System.Windows.Forms.RadioButton radioButtonNormal;
        private System.Windows.Forms.RadioButton radioButtonBelow;
        private System.Windows.Forms.GroupBox groupBoxRestore;
        private System.Windows.Forms.Button buttonResume;
        private System.Windows.Forms.Button buttonRestore;
    }
}

