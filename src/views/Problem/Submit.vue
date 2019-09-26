<template>
  <el-container>
    <el-header :style="{height: 'initial'}">
      <h2>{{ problemInfo.id + ' : ' +problemInfo.title }}</h2>
      <h5>时间: {{ problemInfo.time_limit }} s 内存: {{ problemInfo.memory_limit }} MB</h5>
    </el-header>
    <el-main>
      <Editor></Editor>
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
import Editor from '../../components/Editor/Editor'
export default {
  data () {
    return {
      id: this.$route.query.id
    }
  },
  computed: {
    ...mapState(['problemInfo'])
  },
  methods: {
    ...mapActions(['getProblemInfo'])
  },
  mounted () {
    this.getProblemInfo(this.id)
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
