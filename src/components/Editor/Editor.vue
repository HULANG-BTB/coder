<template>
  <div class="editor">
    <div class="toobar">
      <el-form :inline="true">
        <el-form-item label="语言：">
          <el-select v-model="options.language" placeholder="请选择" @change="languageChange">
            <el-option
              v-for="language in languages"
              :key="language.value"
              :label="language.label"
              :value="language.value">
            </el-option>
          </el-select>
        </el-form-item>
        <el-form-item label="主题：">
          <el-select v-model="options.theme" placeholder="请选择" @change="themeChange">
            <el-option
              v-for="theme in themes"
              :key="theme.value"
              :label="theme.label"
              :value="theme.value">
            </el-option>
          </el-select>
        </el-form-item>
      </el-form>
    </div>
    <div class="content">
      <div ref="editor" class="editor-element"></div>
    </div>
  </div>
</template>

<script>
import * as monaco from 'monaco-editor'
export default {
  data () {
    return {
      themes: [
        {
          label: 'Visual Studio',
          value: 'vs'
        },
        {
          label: 'Visual Studio Dark',
          value: 'vs-dark'
        },
        {
          label: 'High Contrast Dark',
          value: 'hc-black'
        }
      ],
      Editor: null,
      backupValue: ''
    }
  },
  props: {
    languages: {
      type: Array,
      default: function () {
        return [
          {
            label: 'C语言',
            value: 'c'
          },
          {
            label: 'C++',
            value: 'cpp'
          },
          {
            label: 'JAVA',
            value: 'java'
          },
          {
            label: 'Python',
            value: 'python'
          },
          {
            label: 'JavaScript',
            value: 'javascript'
          },
          {
            label: 'SQL',
            value: 'sql'
          }
        ]
      }
    },
    options: {
      type: Object,
      default: function () {
        return {
          selectOnLineNumbers: true,
          roundedSelection: false,
          cursorStyle: 'line', // 光标样式
          automaticLayout: false, // 自动布局
          glyphMargin: true, // 字形边缘
          useTabStops: false,
          fontSize: 20, // 字体大小
          autoIndent: false, // 自动布局
          language: 'c', // 语言
          theme: 'vs', // 主题
          value: this.backupValue // 内容
        }
      }
    }
  },
  mounted () {
    // this.initEditor()
    this.initialize()
  },
  methods: {
    initialize () {
      let that = this
      this.$refs.editor.innerHTML = ''
      this.Editor = monaco.editor.create(this.$refs.editor, this.options)
      this.Editor.onDidChangeModelContent(function (event) {
        that.backupValue = that.Editor.getValue()
      })
    },
    themeChange () {
      this.initialize()
    },
    languageChange () {
      this.initialize()
    }

    // initEditor () {
    //   let self = this
    //   self.$refs.container.innerHTML = ''
    //   self.monacoEditor = monaco.editor.create(self.$refs.container, {
    //     value: self.codesCopy || self.codes,
    //     language: self.language,
    //     theme: self.theme, // vs, hc-black, or vs-dark
    //     editorOptions: self.editorOptions
    //   })
    //   self.$emit('onMounted', self.monacoEditor)// 编辑器创建完成回调
    //   self.monacoEditor.onDidChangeModelContent(function (event) { // 编辑器内容changge事件
    //     self.codesCopy = self.monacoEditor.getValue()
    //     self.$emit('onCodeChange', self.monacoEditor.getValue(), event)
    //   })
    //   // 编辑器随窗口自适应
    //   window.addEventListener('resize', function () {
    //     this.initEditor()
    //   })
    // },
    // RunResult () {
    //   console.log(this.monacoEditor.getValue())
    // },
    // themeChange (val) {
    //   this.initEditor()
    // }
  }
}
</script>

<style scoped>
.editor {
  display: block;
}
.content {
  border: 1px solid #e6e6e6;
}
.editor-element {
  height: 500px;
  width: 100%;
}
</style>
