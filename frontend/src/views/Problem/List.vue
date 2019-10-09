<template>
  <el-container>
    <el-header :style="{height: 'initial'}">
      <el-row style="text-align: center;">
        <el-row>
          <h1>题目列表</h1>
          <el-input placeholder="请输入内容" v-model="keyword" class="input-with-select">
            <el-select v-model="type" slot="prepend" placeholder="请选择">
              <el-option label="题号" value="pid"></el-option>
              <el-option label="标题" value="title"></el-option>
              <el-option label="内容" value="description"></el-option>
              <el-option label="分类" value="category"></el-option>
            </el-select>
            <el-button slot="append" icon="el-icon-search" @click="search"></el-button>
          </el-input>
        </el-row>
      </el-row>
    </el-header>
    <el-main>
      <el-table
        :data="tableData"
        style="width: 100%"
        border
        fit
        @row-click="redirect"
      >
        <el-table-column
          label="编号"
          width="100">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.id }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="标题">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.title }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="分类/来源">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.category }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="提交"
          width="80">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.submit }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="正确"
          width="80">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.accepted }}</span>
          </template>
        </el-table-column>
      </el-table>
    </el-main>
    <el-footer>
      <el-pagination
        @size-change="handleSizeChange"
        @current-change="handlePageChange"
        :current-page="page"
        :page-sizes="[10, 20, 50, 100]"
        :page-size="limit"
        layout="total, sizes, prev, pager, next, jumper"
        :total="total">
      </el-pagination>
    </el-footer>
  </el-container>
</template>

<script>
import {mapActions, mapState} from 'vuex'

export default {
  data () {
    return {
      page: parseInt(this.$route.query.page) || 1,
      limit: parseInt(this.$route.query.limit) || 10,
      keyword: this.$route.query.keyword || '',
      type: this.$route.query.type || 'description'
    }
  },
  computed: {
    tableData () {
      return this.problemList.data
    },
    ...mapState(['problemList']),
    total () {
      return this.problemList.total
    }
  },
  mounted () {
    this.getProblemList(this)
  },
  methods: {
    ...mapActions(['getProblemList']),
    handlePageChange (data) {
      this.page = data
      const query = this.buildQuery()
      this.$router.push({name: 'ProblemList', query: query})
      this.getProblemList(query)
    },
    handleSizeChange (data) {
      this.limit = data
      const query = this.buildQuery()
      this.$router.push({name: 'ProblemList', query: query})
      this.getProblemList(query)
    },
    redirect (obj) {
      this.$router.push({name: 'ProblemDetail', query: {id: obj.id}})
    },
    search () {
      if (this.type !== '') {
        this.page = 1
        const query = this.buildQuery()
        this.$router.push({name: 'ProblemList', query: query})
        this.getProblemList(query)
      }
    },
    buildQuery () {
      return {
        page: this.page,
        limit: this.limit,
        type: this.type,
        keyword: this.keyword
      }
    }
  }
}
</script>

<style scoped>
.el-select {
  width: 150px;
}
</style>
