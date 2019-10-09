<template>
  <el-container>
    <el-header :style="{height: 'initial'}">
      <h2>{{ problemInfo.pid + ' : ' + problemInfo.title }}</h2>
      <h5>时间: {{ problemInfo.time_limit }} s 内存: {{ problemInfo.memory_limit }} MB</h5>
    </el-header>
    <el-main>
      <Editor v-model="formData"></Editor>
    </el-main>
    <el-footer :style="{height: 'initial'}">
      <el-button type="primary" @click.prevent="redirect('submit')">提交代码</el-button>
      <el-button type="primary" @click.prevent="redirect('status')">提交状态</el-button>
    </el-footer>
  </el-container>
</template>

<script>
import {
  mapActions,
  mapState
} from 'vuex'
import {
  reqProblemSubmit
} from '../../api'
import Editor from '../../components/Editor/Editor'
export default {
  data () {
    return {
      id: this.$route.query.id,
      formData: {
        code: '',
        language: 'c'
      }
    }
  },
  computed: {
    ...mapState(['problemInfo', 'userInfo'])
  },
  methods: {
    ...mapActions(['getProblemInfo']),
    redirect (type) {
      if (type === 'submit') {
        if (!this.userInfo.username) {
          this.$message('请先登录！')
        } else {
          this.submit()
        }
      } else {
        this.$router.replace({name: 'ProblemDetail'})
      }
    },
    async submit () {
      const query = this.buildQuery()
      const result = await reqProblemSubmit(query)
      if (result.code === 1) {
        this.$router.push({name: 'StatusList', query: { page: 1, limit: 10 }})
      } else {
        this.$message(result.msg)
      }
    },
    buildQuery () {
      return {
        pid: this.problemInfo.pid,
        code: this.formData.code,
        language: this.formData.language
      }
    }
  },
  mounted () {
    this.getProblemInfo({id: this.id})
  },
  components: {
    Editor
  }
}
</script>

<style scoped>
  .el-header {
    text-align: center;
  }
  .el-main {
    box-shadow: 0 2px 4px rgba(0, 0, 0, .12), 0 0 6px rgba(0, 0, 0, .12);
    border-radius: 4px;
  }
  .el-footer {
    margin-top: 10px;
    box-shadow: 0 2px 4px rgba(0, 0, 0, .12), 0 0 6px rgba(0, 0, 0, .12);
    border-radius: 4px;
    text-align: center;
    padding: 10px;
  }
  p {
    padding: 0 15px;
    border-radius: 4px;
    border-left: solid 1px #e6e6e6;
  }
</style>
